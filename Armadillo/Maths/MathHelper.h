#pragma once
#include "VectorMath.h"

namespace Armadillo
{
	namespace Maths
	{
		template<class T>
		const T& Clamp(const T& x, const T& a, const T& b)
		{
			return x < a ? a : (x > b ? b : x);
		}

		template<class T>
		const T& Max(const T& a, const T& b)
		{
			return (a < b) ? b : a;
		}

		extern float BarryCentric(Armadillo::Maths::Vector3 p1, Armadillo::Maths::Vector3 p2, Armadillo::Maths::Vector3 p3, Armadillo::Maths::Vector2 pos);
	}
}