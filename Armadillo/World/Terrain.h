#pragma once
#include "../Maths/VectorMath.h"
#include "Biome.h"
#include <vector>

namespace Armadillo
{
	namespace World
	{
		class TerrainData;
		class TerrainBuffer;

		class Terrain
		{
		private:
			//Private Attributes
			Biome biome;
			TerrainData* data;
			TerrainBuffer* buffer;
		public:
			//Public Attributes
			Maths::Vector3 Position;
			Maths::Vector2i Grid;
			float Scale;		

			//Constructors
			Terrain();
			Terrain(Maths::Vector3, float);	

			//Public Getter Methods
			bool Contains(float, float, float);
			float GetHeight(float, float);
			float GetHeight(Maths::Vector3);
			TerrainData* GetTerrainData();
			TerrainBuffer* GetTerrainBuffer();
			Biome& GetBiome();

			//Public Setter Methods
			void SetTerrainData(TerrainData*);			
			void SetTerrainBuffer(TerrainBuffer*);
		};
	}
}