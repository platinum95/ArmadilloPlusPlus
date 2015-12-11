#pragma once
#include <vector>

namespace Armadillo
{
	namespace World
	{
		enum BiomeType
		{
			Snow,
			Tundra, 
			Bare,
			Scorched,
			Taiga, 
			Shrubland,
			TemperateDesert,
			TemperateRainForest,
			TemperateDeciduousForest,
			Grassland,
			TropicalRainForest,
			TropicalSeasonalForest,
			SubtropicalDesert
		};

		extern std::vector<BiomeType> BiomeTable;
		extern std::vector<BiomeType> GenerateBiomeTable();

		class Biome
		{
		private:
			int moisture;
			int elevation;

			void Init();
			
		public:
			BiomeType Type;

			//Constructors
			Biome();
			Biome(float, float);			
		};
	}
}