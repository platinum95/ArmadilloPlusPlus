#pragma once
#include <vector>
#include "../Maths/VectorMath.h"

namespace Armadillo
{
	namespace World
	{
		class TerrainData
		{
		private:
			//Private Data
			std::vector<float> heights;
			std::vector<float> normals;
			float spread;

			//Private Ray Searching
			Maths::Vector3 BinarySearch(int, float, float, Maths::Vector3&);
			bool IntersectionInRange(float, float, Maths::Vector3&);
			bool IsUnderTerrain(Maths::Vector3&);

			//Normal Generation
			Armadillo::Maths::Vector3 CalculateNormal(int x, int y);
		public:
			//Public Optimize Attributes
			bool Stitched[3];

			int Length;
			int LengthSquared;

			Armadillo::Maths::Vector2i NoiseCoord;

			//Constructors
			TerrainData();

			//Public Setters
			void SetNoiseCoord(int, int);
			void SetNoiseCoord(Maths::Vector2i);
			void SetHeightData(std::vector<float>, float);
			void SetNormalData(std::vector<float>);

			//Stitching
			void SetHeightVertical(TerrainData*);
			void SetHeightHorizontal(TerrainData*);
			void SetHeightCorner(TerrainData*);

			//External Height Getter/Setter
			void SetHeight(int, int, float);
			float GetHeight(int, int);
			float GetNormal(int, int, int);
			float GetHeight(float, float, Maths::Vector3);
			float GetHeight(Maths::Vector3, Maths::Vector3);

			void GenerateNormals();

			std::vector<float>& GetHeights();
			std::vector<float>& GetNormals();
		};
	}
}