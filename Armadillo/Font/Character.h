#pragma once
#include <string>
#include "../Maths/VectorMath.h"

namespace Armadillo
{
	namespace Font
	{
		using namespace Armadillo::Maths;

		class Character
		{
		public:
			int id;
			Armadillo::Maths::Vector2 TextureCoord;
			Armadillo::Maths::Vector2 MaxTextureCoord;
			Armadillo::Maths::Vector2 Offset;
			Armadillo::Maths::Vector2 Size;
			float Advance;

			Character() { };
			Character(int, float, float, float, float, float, float, float, float, float);			
		};
	}
}
