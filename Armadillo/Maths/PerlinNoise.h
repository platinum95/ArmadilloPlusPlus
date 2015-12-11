#pragma once
#include <vector>
#include "Random.h"

namespace Armadillo
{
	namespace Maths
	{
		class Noise
		{
		private:
			static Random rand;			
						
		public:
			static double Sample(double, double);
			static double InterpolateSample(double, double);
			static double Interpolate(double, double, double);
			static std::vector<float> Generate(int, int, int, int, double, double, int);
		};
	}
}