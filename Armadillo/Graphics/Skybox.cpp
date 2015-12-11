#include "Skybox.h"
#include "GL\glew.h"

namespace Armadillo
{
	namespace Graphics
	{
		Skybox::Skybox()
		{

		}

		Skybox::Skybox(Armadillo::Maths::Vector3 c, float d, float g)
		{
			this->SkyColour = c;
			this->Density = d;
			this->Gradient = g;
		}

		FloatBuffer* Skybox::CubeBuffer()
		{
			float f = 500.0f;

			float vertices[36*3] = {
				-f, f, -f,
				-f, -f, -f,
				f, -f, -f,
				f, -f, -f,
				f, f, -f,
				-f, f, -f,

				-f, -f, f,
				-f, -f, -f,
				-f, f, -f,
				-f, f, -f,
				-f, f, f,
				-f, -f, f,

				f, -f, -f,
				f, -f, f,
				f, f, f,
				f, f, f,
				f, f, -f,
				f, -f, -f,

				-f, -f, f,
				-f, f, f,
				f, f, f,
				f, f, f,
				f, -f, f,
				-f, -f, f,

				-f, f, -f,
				f, f, -f,
				f, f, f,
				f, f, f,
				-f, f, f,
				-f, f, -f,

				-f, -f, -f,
				-f, -f, f,
				f, -f, -f,
				f, -f, -f,
				-f, -f, f,
				f, -f, f
			};
			return new FloatBuffer(3, vertices, 36, GL_STATIC_DRAW);
		}
	}
}