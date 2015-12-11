#include "TerrainFactory.h"
#include "TerrainData.h"
#include "Terrain.h"
#include "../Maths/PerlinNoise.h"
#include "../Osiris.h"

namespace Armadillo
{
	namespace World
	{
		using namespace Armadillo::Maths;
		using namespace std;

		TerrainFactory::TerrainFactory()
		{
			
		}

		TerrainFactory::TerrainFactory(Seed* s)
		{
			this->seed = s;
			this->Lamda = 1.0f;
		}

		Vector3 TerrainFactory::GridPosition(int i, int j)
		{
			return Vector3(i * (seed->Width - 1) * seed-> WidthSpread, 0, j * (seed-> Height - 1) * seed-> WidthSpread);
		}
		
		vector<float> TerrainFactory::Noise(int x, int y)
		{
			std::vector<float> noise1 = Noise::Generate(x * seed-> Width, y * seed-> Height, seed-> Width, seed-> Height, seed-> Zoom, seed-> Persistance, seed-> Octaves);
			for (int i = 0; i < seed-> WidthHeight; i++)
			{
				noise1[i] = seed-> HeightSpread * pow(Osiris::ConstantE, Lamda * noise1[i]);
			}
			return noise1;
		}

		Vector3 TerrainFactory::WaterPosition(int x, int z)
		{
			float Scale = WaterScale();
			Vector3 pos = this->GridPosition(x, z);
			pos.x += Scale;
			pos.y = Osiris::WorldWaterHeight;
			pos.z += Scale;
			return pos;
		}

		float TerrainFactory::WaterScale()
		{
			return seed-> WidthSpread * (seed-> Width - 1) / 2;
		}

		TerrainData* TerrainFactory::GenerateData(int x, int y)
		{
			TerrainData* terrain = new TerrainData();
			terrain->SetHeightData(Noise(x, y), seed->WidthSpread);
			terrain->GenerateNormals();
			terrain->SetNoiseCoord(x, y);
			return terrain;
		}

		Terrain* TerrainFactory::GenerateTerrain(int x, int z, Vector2i offset)
		{
			Terrain* t = new Terrain(this->GridPosition(x + offset.x, z + offset.y), 1.0f);
			t->Grid.x = x + offset.x;
			t->Grid.y = z + offset.y;
			return t;
		}
	}
}