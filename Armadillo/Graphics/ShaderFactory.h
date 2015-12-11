#pragma once
#include "Shader.h"
#include <string>

namespace Armadillo
{
	namespace Graphics
	{
		class ShaderFactory
		{
		private:
			Shader* shader;

		public:
			ShaderFactory();
			~ShaderFactory();

			ShaderFactory* Load(std::string, std::string);
			Shader* Compile();
			ShaderFactory* RegisterAttribute(std::string);
			ShaderFactory* RegisterUniform(std::string);
			ShaderFactory* RegisterTexture(std::string, int);
		};
	}
}