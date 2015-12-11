#pragma once

namespace Armadillo
{
	namespace World
	{
		class Seed
		{
		public:
			int Width, Height;
			int WidthHeight;
			int Octaves;
			float Persistance, Zoom;
			float WidthSpread, HeightSpread;			

			Seed();			
			Seed(int, int, float, float, float, float, int);
		};
	}
}