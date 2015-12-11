#pragma once
#include "VectorMath.h"
#include "VertexBuffer.h"
#include "Font.h"
#include <string>

namespace Armadillo
{
	namespace Font
	{
		class Text
		{
		private:
			Armadillo::Graphics::VertexBuffer* vBuffer;
			int lineCount;
			float lineWidth;
			bool centered;

			Font* font;

		public:
			std::string Line;
			float Size;

			Armadillo::Maths::Vector3 Colour;
			Armadillo::Maths::Vector2 Position;

			Text();
			Text(std::string, float, Armadillo::Maths::Vector2, float, int);

			void CreateFloatBuffer();
			void Remove();
			void Centre(bool);
		};
	}
}