#include "FrameEffect.h"
#include "GL\glew.h"

namespace Armadillo
{
	namespace Graphics
	{
		FloatBuffer* FrameEffect::GetScreenQuadBuffer()
		{
			float quadArray[8] = {
				-1, -1,
				1, -1,
				-1, 1,
				1, 1 };
			return new Armadillo::Graphics::FloatBuffer(2, quadArray, 4, GL_STATIC_DRAW);
		}
	}
}