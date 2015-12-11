#pragma once
#include <vector>
#include "../Maths/VectorMath.h"

namespace Armadillo
{
	namespace World
	{
		class Seed;
		class TerrainData;
		class Terrain;

		class TerrainFactory
		{
		private:			
			//Private Methods
			std::vector<float> Noise(int, int);
			float Lamda;
		public:	
			//Public Attributes
			Seed* seed;

			//Constructors
			TerrainFactory();
			TerrainFactory(Seed*);

			//Public Methods
			TerrainData* GenerateData(int, int);
			Terrain* GenerateTerrain(int, int, Maths::Vector2i);

			//World Helper Methods
			Maths::Vector3 GridPosition(int, int);
			Maths::Vector3 WaterPosition(int, int);
			float WaterScale();
		};
	}
}