#include "Texture.h"
#include "GL\glew.h"
#include "lodepng.h"

namespace Armadillo
{
	namespace Graphics
	{
		Texture::Texture(int i, int j, int k, int l)
		{
			this->Id = i;
			this->Width = j;
			this->Height = k;
			this->Count = l;
			this->Offset = Armadillo::Maths::Vector2(0, 0);
		}

		Texture::~Texture()
		{

		}

		void Texture::Bind()
		{			
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, this->Id);
		}

		void Texture::UnBind()
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void Texture::Dispose()
		{
			GLuint id = this->Id;
			glDeleteTextures(1, &id);
		}

		Texture* Texture::LoadTexture(std::string path)
		{
			std::vector<unsigned char> image;
			unsigned width, height;
			unsigned error = Armadillo::Graphics::LodePng::decode(image, width, height, path);

			if (error != 0)
				return NULL;

			GLuint Id;
			glGenTextures(1, &Id);
			glBindTexture(GL_TEXTURE_2D, Id);

			glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());

			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_MAX_TEXTURE_LOD_BIAS, -0.4f);

			return new Texture(Id, width, height, 1);
		}

		Texture* Texture::LoadCubeTexture(std::vector<std::string> paths)
		{
			GLuint Id;
			glGenTextures(1, &Id);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, Id);

			unsigned width, height;
			int size = paths.size();
			for (int i = 0; i < size; i++)
			{
				std::vector<unsigned char> image;				
				unsigned error = Armadillo::Graphics::LodePng::decode(image, width, height, paths[i]);

				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.data());
			}
			glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			return new Texture(Id, width, height, size);
		}

		void Texture::SaveTexture(std::vector<unsigned char> image, int width, int height, std::string path)
		{
			unsigned error = Armadillo::Graphics::LodePng::encode(path, image.data(), width, height);
		}
	}
}