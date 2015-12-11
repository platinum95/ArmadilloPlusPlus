#include "Biome.h"
#include "../Maths/PerlinNoise.h"
#include "../Maths/MathHelper.h"

namespace Armadillo
{
	namespace World
	{
		std::vector<BiomeType> BiomeTable = GenerateBiomeTable();

		std::vector<BiomeType> GenerateBiomeTable()
		{
			std::vector<BiomeType> table = std::vector<BiomeType>(6 * 4);
			int i = 0;
			table[i++] = SubtropicalDesert;
			table[i++] = Grassland;
			table[i++] = table[i++] = TropicalSeasonalForest;
			table[i++] = table[i++] = TropicalRainForest;
			table[i++] = TemperateDesert;
			table[i++] = table[i++] = Grassland;
			table[i++] = table[i++] = TemperateDeciduousForest;
			table[i++] = TemperateRainForest;
			table[i++] = table[i++] = TemperateDesert;
			table[i++] = table[i++] = Shrubland;
			table[i++] = table[i++] = Taiga;
			table[i++] = Scorched;
			table[i++] = Bare;
			table[i++] = Tundra;
			table[i++] = table[i++] = table[i++] = Snow;
			return table;
		}

		Biome::Biome()
		{

		}

		Biome::Biome(float x, float z)
		{
			this->moisture = Armadillo::Maths::Clamp((int)abs(6 * Armadillo::Maths::Noise::Sample(x, z)), 1, 6);
			this->elevation = Armadillo::Maths::Clamp((int)abs(4 * Armadillo::Maths::Noise::InterpolateSample(x, z)), 1, 4);
			this->Init();
		}

		void Biome::Init()
		{
			this->Type = BiomeTable[this->moisture + this->elevation * 6];
		}
	}
}