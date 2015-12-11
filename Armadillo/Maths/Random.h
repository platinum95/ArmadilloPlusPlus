#pragma once
#include <random>

namespace Armadillo
{
	namespace Maths
	{
		class Random
		{
		private:
			long seed;
			double mean, deviation;
			std::default_random_engine generator;

		public:
			Random();
			Random(long);

			int NextInt();
			int NextInt(int);
			bool NextBoolean();
			float NextFloat();
			double NextDouble();
			void SetSeed(long);
			char NextChar();
			double NextGaussian();
			double NextGaussian(double, double);
			void SetGaussian(double, double);
		};
	}
}