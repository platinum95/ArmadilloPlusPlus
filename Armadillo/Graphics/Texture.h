#pragma once
#include <vector>
#include <string>
#include "../Maths/VectorMath.h"
#include "../Management/IDisposable.h"

namespace Armadillo
{
	namespace Graphics
	{
		class Texture : public IDisposable
		{
		public:
			//Static Methods
			static Texture* LoadTexture(std::string);
			static Texture* LoadCubeTexture(std::vector<std::string>);
			static void Texture::SaveTexture(std::vector<unsigned char>, int, int, std::string);
			static void DefaultParameters();
		
			//Constructors
			Texture(int, int, int, int);
			~Texture();

			//Opengl Call Methods
			void Bind();
			void UnBind();
			void Dispose();

			int Id;
			int Width;
			int Height;
			int Count;
			Armadillo::Maths::Vector2 Offset;
		};
	}
}