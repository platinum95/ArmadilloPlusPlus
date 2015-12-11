#pragma once
#include "FloatBuffer.h"
#include "../Maths/VectorMath.h"

namespace Armadillo
{
	namespace Graphics
	{
		class Skybox
		{
		public:
			Armadillo::Maths::Vector3 SkyColour;
			float Density, Gradient;

			Skybox();
			Skybox(Armadillo::Maths::Vector3, float, float);

			static FloatBuffer* CubeBuffer();
		};
	}
}