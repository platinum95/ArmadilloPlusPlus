#pragma once
#include "../Maths/VectorMath.h"

namespace Armadillo
{
	namespace World
	{
		enum CartesianSpin
		{
			Clockwise = 0,
			AntiClockWise = 1
		};

		enum CartesianAxis
		{
			North = 0,
			East = 1,
			South = 2,
			West = 3,
			Up
		};

		extern CartesianAxis Rotate(CartesianAxis, CartesianSpin);
		extern CartesianAxis Flip(CartesianAxis);
		extern CartesianAxis ToAxis(Armadillo::Maths::Vector2);
	}
}