#include "Direction.h"

namespace Armadillo
{
	namespace World
	{
		CartesianAxis Rotate(CartesianAxis a, CartesianSpin s)
		{
			return (s == 0) ? (CartesianAxis)((a + 1) % 4) : (CartesianAxis)((a - 1) % 4);
		}

		CartesianAxis Flip(CartesianAxis a)
		{
			return (CartesianAxis)((a + 2) % 4);
		}

		CartesianAxis ToAxis(Armadillo::Maths::Vector2 v)
		{
			if (v.x < 0)
				return West;
			if (v.x > 0)
				return East;
			if (v.y < 0)
				return South;
			if (v.y > 0)
				return North;
			return Up;
		}
	}
}