#include "Terrain.h"
#include "../Maths/MathHelper.h"
#include "TerrainData.h"
#include <cmath>

namespace Armadillo
{
	namespace World
	{
		using namespace Armadillo::Maths;		

		Terrain::Terrain()
		{
			
		}

		Terrain::Terrain(Vector3 pos, float s)
		{
			this->Position = pos;
			this->Scale = s;
		}

		bool Terrain::Contains(float x, float z, float Size)
		{
			return x >= this->Position.x && z >= this->Position.z && x < this->Position.x + Size && z < this->Position.z + Size;
		}

		float Terrain::GetHeight(float x, float z)
		{
			return this->data->GetHeight(x, z, this->Position);
		}

		float Terrain::GetHeight(Vector3 pos)
		{
			return this->data->GetHeight(pos, this->Position);
		}

		TerrainData* Terrain::GetTerrainData()
		{
			return this->data;
		}

		TerrainBuffer* Terrain::GetTerrainBuffer()
		{
			return this->buffer;
		}

		Biome& Terrain::GetBiome()
		{
			return this->biome;
		}

		void Terrain::SetTerrainData(TerrainData* data)
		{
			this->data = data;
		}

		void Terrain::SetTerrainBuffer(TerrainBuffer* buffer)
		{
			this->buffer = buffer;
		}
	}
}