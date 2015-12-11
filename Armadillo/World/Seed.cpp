#include "Seed.h"

namespace Armadillo
{
	namespace World
	{
		Seed::Seed()
		{

		}

		Seed::Seed(int i, int j, float x, float y, float z, float w, int k)
		{
			this->Width = i;
			this->Height = j;
			this->WidthSpread = x;
			this->HeightSpread = y;
			this->Zoom = z;
			this->Persistance = w;
			this->WidthHeight = i * j;
			this->Octaves = k;
		}
	}
}