#include "TerrainManager.h"
#include "Water.h"
#include "Terrain.h"
#include "TerrainData.h"
#include "TerrainBuffer.h"
#include "Direction.h"

#include "../Management/Logger.h"
#include "../Osiris.h"
#include "../Maths/MathHelper.h"
#include "../Graphics/View.h"
#include "../Graphics/IndexBuffer.h"

#include <GL\glew.h>
#include <algorithm>
#include <cmath>

namespace Armadillo
{
	namespace World
	{
		using namespace Armadillo::Maths;
		using namespace Armadillo::Graphics;
		using namespace std;

		TerrainManager::TerrainManager()
		{

		}

		TerrainManager::TerrainManager(Seed* s, View* v)
		{
			this->seed = s;
			this->view = v;
			this->tFactory = TerrainFactory(s);
			this->Size = s->Width * s->WidthSpread;
			this->Width = (int)ceil(Osiris::DisplayFarPlane / Size) + Osiris::TerrainGenerationBoost;;
			this->WidthSquared = Width * Width;
			this->indexBuffers = vector<IndexBuffer*>(Osiris::TerrainIndexBufferCount);
			this->waters = vector<Water*>(this->WidthSquared);
			this->terrains = vector<Terrain*>(this->WidthSquared);
			this->terrainDatas = vector<TerrainData*>(this->WidthSquared);
			this->terrainBuffers = vector<TerrainBuffer*>(this->WidthSquared);
			this->Init();
		}

		void TerrainManager::Generate()
		{
			if (this->RequireGenerate())
			{
				Vector2 central = this->GetMidPoint(this->GetCentrePoint(this->cornerPoint, this->Width), this->GetCentrePoint(this->lastCornerPoint, this->Width));

				CartesianAxis dir = ToAxis(this->lastCornerPoint - this->cornerPoint);				
			}
		}

		IndexBuffer* TerrainManager::GetIndexBuffer(int index)
		{
			return this->indexBuffers[index];
		}

		void TerrainManager::Init()
		{
			this->InitDefaultData();
			this->InitIndexBuffers();
			this->InitWater();
			this->InitTerrain();
			this->StitchData();
			this->InitTerrainBuffers();
		}
		
		void TerrainManager::InitIndexBuffers()
		{
			for (int i = 0; i < Osiris::TerrainIndexBufferCount; i++)
			{
				this->GenerateIndexBuffer(i);
			}
		}

		void TerrainManager::InitDefaultData()
		{
			this->fPositions = std::vector<float>(2 * seed->WidthHeight);
			for (int j = 0; j < seed->Height; j++)
			{
				for (int i = 0; i < seed->Width; i++)
				{
					fPositions[2 * (i + j * seed->Width)] = i * seed->WidthSpread;
					fPositions[2 * (i + j * seed->Width) + 1] = j * seed->WidthSpread;
				}
			}
		}

		void TerrainManager::InitPoints()
		{
			this->cornerPoint = Vector2i(
				floor(this->view->Position.x / this->Size) - this->Width / 2,
				floor(this->view->Position.z / this->Size) - this->Width / 2);
			this->lastCornerPoint = Vector2i();
		}

		void TerrainManager::InitWater()
		{
			for (int j = 0; j < this->Width; j++)
			{
				for (int i = 0; i < this->Width; i++)
				{
					this->waters[i + j * this->Width] = new Water(this->tFactory.WaterPosition(i + this->cornerPoint.x, j + this->cornerPoint.y), this->tFactory.WaterScale());
				}
			}
		}

		void TerrainManager::InitTerrain()
		{
			for (int j = 0; j < this->Width; j++)
			{
				for (int i = 0; i < this->Width; i++)
				{
					Terrain* t = this->tFactory.GenerateTerrain(i, j, this->cornerPoint);
					TerrainData* td = this->tFactory.GenerateData(i + this->cornerPoint.x, j + this->cornerPoint.y);

					t->SetTerrainData(td);

					this->terrains[i + j * this->Width] = t;
					this->terrainDatas[i + j * this->Width] = td;
				}
			}
		}

		void TerrainManager::InitTerrainBuffers()
		{
			for (int j = 0; j < this->Width; j++)
			for (int i = 0; i < this->Width; i++)
			{
				TerrainBuffer* vBuffer = new TerrainBuffer(this->fPositions);

				vBuffer->Evict();
				vBuffer->BufferData(this->terrainDatas[i + j * this->Width]);

				this->terrains[i + j * this->Width]->SetTerrainBuffer(vBuffer);
				this->terrainBuffers[i + j * this->Width] = vBuffer;			
			}
		}

		bool TerrainManager::RequireGenerate()
		{
			Vector2i pos = Vector2i(
				floor(this->view->Position.x / this->Size) - this->Width / 2, 
				floor(this->view->Position.z / this->Size) - this->Width / 2);

			if (!(pos == this->cornerPoint))
			{
				this->lastCornerPoint = this->cornerPoint;
				this->cornerPoint = pos;
				return true;
			}
			return false;
		}

		Vector2 TerrainManager::GetCentrePoint(Vector2i nmPoint, int Width)
		{
			return Vector2((float)nmPoint.x + (float)Width / 2.0f, (float)nmPoint.y + (float)Width / 2.0f);
		}

		Vector2 TerrainManager::GetMidPoint(Vector2 p1, Vector2 p2)
		{
			return Vector2((p1.x + p2.x) / 2, (p1.y + p2.y));
		}

		void TerrainManager::GenerateIndexBuffer(int level = 0)
		{
			int increment = pow(2, level);
			int size = 6 * (seed->Width - increment) * (seed->Height - increment);
			if (size == 0) return;
			std::vector<int> indices = std::vector<int>(size);
			int pointer = 0;
			int topLeft, topRight, bottomLeft, bottomRight;
			for (int j = 0; j < seed->Height - 1; j += increment)
			{
				for (int i = 0; i < seed->Width - 1; i += increment)
				{
					topLeft = j * seed->Width + i;
					topRight = topLeft + increment;
					bottomLeft = (j + increment) * seed->Width + i;
					bottomRight = bottomLeft + increment;
					indices[pointer++] = topLeft;
					indices[pointer++] = bottomLeft;
					indices[pointer++] = topRight;
					indices[pointer++] = topRight;
					indices[pointer++] = bottomLeft;
					indices[pointer++] = bottomRight;
				}
			}
			IndexBuffer* iBuffer = new IndexBuffer(GL_UNSIGNED_INT);
			iBuffer->SetData(indices.data(), size, GL_STATIC_DRAW);
			this->indexBuffers[level] = iBuffer;
		}		

		TerrainData* TerrainManager::SearchStoredData(int x, int z)
		{
			for (TerrainData* t : this->terrainDatas)
			{
				if (t != NULL)
				if (t->NoiseCoord.x == x && t->NoiseCoord.y == z)
					return t;
			}
			return NULL;
		}

		void TerrainManager::StitchData()
		{
			TerrainData* t = NULL;
			TerrainData* g = NULL;			
			for (int j = 0; j < this->Width; j++)
			{
				for (int i = 0; i < this->Width; i++)
				{
					t = this->terrains[this->Index(i, j)]->GetTerrainData();
					if (t == NULL)
						return;

					if (this->InRange(i + 1, j))
					{
						g = this->terrains[this->Index(i + 1, j)]->GetTerrainData();
						if (!t->Stitched[0])
							if (g != NULL)
								t->SetHeightVertical(g);
					}
					if (this->InRange(i, j + 1))
					{
						g = this->terrains[this->Index(i, j + 1)]->GetTerrainData();
						if (!t->Stitched[1])
							if (g != NULL)
								t->SetHeightHorizontal(g);
					}
					if (this->InRange(i + 1, j + 1))
					{
						g = this->terrains[this->Index(i + 1, j + 1)]->GetTerrainData();
						if (!t->Stitched[2])
							if (g != NULL)
								t->SetHeightCorner(g);
					}
					t->GenerateNormals();
				}
			}
		}

		int TerrainManager::Index(int x, int z)
		{
			return x + z * this->Width;
		}

		bool TerrainManager::InRange(int x, int z)
		{
			return x >= 0 && z >= 0 && x < this->Width && z < this->Width;
		}

		vector<TerrainBuffer*>& TerrainManager::GetTerrainBuffers()
		{
			return this->terrainBuffers;
		}

		vector<Water*>& TerrainManager::GetWaters()
		{
			return this->waters;
		}

		vector<Terrain*>& TerrainManager::GetTerrains()
		{
			return this->terrains;
		}

		float TerrainManager::GetHeight(float x, float z)
		{
			Terrain* t = this->GetTerrain(x, z);
			return t != NULL ? t->GetHeight(x, z) : 0;
		}

		Terrain* TerrainManager::GetTerrain(float x, float z)
		{
			for (Terrain* t : this->terrains)
			{
				if (t->Contains(x, z, this->Size))
					return t;
			}
			return NULL;
		}
	}
}