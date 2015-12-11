#include "TerrainData.h"
#include "../Maths/MathHelper.h"

namespace Armadillo
{
	namespace World
	{
		using namespace std;
		using namespace Armadillo::Maths;

		TerrainData::TerrainData()
		{
			this->Stitched[3] = { false };
		}

		void TerrainData::SetNoiseCoord(int i, int j)
		{
			this->NoiseCoord = Vector2i(i, j);
		}

		void TerrainData::SetNoiseCoord(Vector2i v)
		{
			this->NoiseCoord = v;
		}

		void TerrainData::SetHeightData(vector<float> hs, float f)
		{
			this->heights = hs;
			this->LengthSquared = hs.size();
			this->Length = (int)sqrt(this->LengthSquared);
			this->spread = f;
			this->normals = vector<float>(3 * hs.size());
		}

		void TerrainData::SetNormalData(vector<float> ns)
		{
			this->normals = ns;
		}

		void TerrainData::SetHeightVertical(TerrainData* t)
		{
			int LengthMinusOne = this->Length - 1;
			for (int i = 0; i < LengthMinusOne; i++)
			{
				this->heights[LengthMinusOne + i * this->Length] = t->GetHeight(0, i);
			}
			this->Stitched[0] = true;
		}

		void TerrainData::SetHeightHorizontal(TerrainData* t)
		{
			int LengthMinusOne = this->Length - 1;
			int LengthMinusOneLength = LengthMinusOne * this->Length;
			for (int i = 0; i < LengthMinusOne; i++)
			{
				this->heights[i + LengthMinusOneLength] = t->GetHeight(i, 0);
			}
			this->Stitched[1] = true;
		}

		void TerrainData::SetHeightCorner(TerrainData* t)
		{
			this->heights[this->heights.size() - 1] = t->GetHeight(0, 0);
			int size = this->normals.size() - 1;
			this->Stitched[2] = true;
		}

		void TerrainData::SetHeight(int x, int z, float f)
		{
			this->heights[x + z * Length] = f;
		}

		float TerrainData::GetHeight(int x, int y)
		{
			if (x < 0)
				return GetHeight(x + 1, y);
			else if (y < 0)
				return GetHeight(x, y + 1);
			else if (x >= this->Length)
				return GetHeight(x - 1, y);
			else if (y >= this->Length)
				return GetHeight(x, y - 1);
			else
				return this->heights[x + y * this->Length];
		}

		float TerrainData::GetNormal(int x, int z, int axis)
		{
			return this->normals[x + axis + z * Length];
		}

		float TerrainData::GetHeight(float x, float z, Vector3 pos)
		{
			float tX = x - pos.x;
			float tZ = z - pos.z;
			int gX = Clamp((int)floor(tX / this->spread), 0, this->Length - 2);
			int gZ = Clamp((int)floor(tZ / this->spread), 0, this->Length - 2);

			float xCoord = ((int)tX % (int)this->spread) / this->spread;
			float zCoord = ((int)tZ % (int)this->spread) / this->spread;
			float result;
			if (xCoord <= (1 - zCoord))
			{
				result = BarryCentric(
					Armadillo::Maths::Vector3(0, heights[gX + Length * gZ], 0),
					Armadillo::Maths::Vector3(1, heights[gX + 1 + Length * gZ], 0),
					Armadillo::Maths::Vector3(0, heights[gX + Length * (gZ + 1)], 1),
					Armadillo::Maths::Vector2(xCoord, zCoord));
			}
			else
			{
				result = BarryCentric(
					Armadillo::Maths::Vector3(1, heights[gX + 1 + Length * gZ], 0),
					Armadillo::Maths::Vector3(1, heights[gX + 1 + Length * (gZ + 1)], 1),
					Armadillo::Maths::Vector3(0, heights[gX + Length * (gZ + 1)], 1),
					Armadillo::Maths::Vector2(xCoord, zCoord));
			}
			return result + pos.y;
		}

		float TerrainData::GetHeight(Vector3 v, Vector3 pos)
		{
			return this->GetHeight(v.x, v.z, pos);
		}

		void TerrainData::GenerateNormals()
		{
			Vector3 n;
			for (int j = 0; j < this->Length; j++)
			{
				for (int i = 0; i < this->Length; i++)
				{
					n = this->CalculateNormal(i, j);
					this->normals[3 * (i + j * this->Length)] = n.x;
					this->normals[3 * (i + j * this->Length) + 1] = n.y;
					this->normals[3 * (i + j * this->Length) + 2] = n.z;
				}
			}
		}

		vector<float>& TerrainData::GetHeights()
		{
			return this->heights;
		}

		vector<float>& TerrainData::GetNormals()
		{
			return this->normals;
		}

		Vector3 TerrainData::BinarySearch(int, float, float, Vector3&)
		{
			return Vector3();
		}

		bool TerrainData::IntersectionInRange(float, float, Vector3&)
		{
			return true;
		}

		bool TerrainData::IsUnderTerrain(Vector3&)
		{
			return false;
		}

		Vector3 TerrainData::CalculateNormal(int x, int y)
		{
			float left = GetHeight(x - 1, y);
			float right = GetHeight(x + 1, y);
			float down = GetHeight(x, y - 1);
			float up = GetHeight(x, y + 1);

			return Vector3::Normalisation(Vector3(left - right, 2.0f, down - up));
		}
	}
}