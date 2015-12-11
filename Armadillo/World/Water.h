#pragma once
#include "../Maths/VectorMath.h"
#include "../Graphics/FrameBuffer.h"
#include "../Graphics/FloatBuffer.h"

namespace Armadillo
{
	namespace World
	{
		class Water
		{
		public:
			Armadillo::Maths::Vector3 Position;
			Armadillo::Maths::Vector3 Colour;
			float Scale;

			Water(Armadillo::Maths::Vector3, float);
			Water(Armadillo::Maths::Vector3, Armadillo::Maths::Vector3, float);
			~Water();

			static Armadillo::Graphics::FrameBuffer* ReflectionBuffer(int, int);
			static Armadillo::Graphics::FrameBuffer* RefractionBuffer(int, int);
			static Armadillo::Graphics::FloatBuffer* QuadBuffer();
		};
	}
}