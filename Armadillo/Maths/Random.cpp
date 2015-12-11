#include "Random.h"
#include <time.h>

namespace Armadillo
{
	namespace Maths
	{
		Random::Random() : Random(time(NULL))
		{

		}

		Random::Random(long l)
		{
			this->seed = l;
			srand(this->seed);
			this->mean = 0;
			this->deviation = 1;
		}

		int Random::NextInt()
		{
			return rand();
		}

		int Random::NextInt(int i)
		{
			return rand() % i;
		}

		bool Random::NextBoolean()
		{
			return rand() % 1 == 0 ? false: true;
		}

		float Random::NextFloat()
		{
			return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		}

		double Random::NextDouble()
		{
			return static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
		}

		void Random::SetSeed(long l)
		{
			this->seed = l;
		}

		char Random::NextChar()
		{
			return rand();
		}

		double Random::NextGaussian()
		{			
			std::normal_distribution<double> dist(this->mean, this->deviation);
			return dist(this->generator);
		}

		double Random::NextGaussian(double m, double d)
		{
			this->mean = m;
			this->deviation = d;
			std::normal_distribution<double> dist(this->mean, this->deviation);
			return dist(this->generator);
		}

		void Random::SetGaussian(double m, double d)
		{
			this->mean = m;
			this->deviation = d;
		}
	}
}