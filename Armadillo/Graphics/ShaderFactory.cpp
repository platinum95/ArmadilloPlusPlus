#include "ShaderFactory.h"

namespace Armadillo
{
	namespace Graphics
	{
		ShaderFactory::ShaderFactory()
		{
			this->shader = NULL;
		}

		ShaderFactory::~ShaderFactory()
		{

		}

		ShaderFactory* ShaderFactory::Load(std::string v, std::string f)
		{
			this->shader = new Shader(v, f);
			return this;
		}

		Shader* ShaderFactory::Compile()
		{
			this->shader->Compile();
			return this->shader;
		}

		ShaderFactory* ShaderFactory::RegisterAttribute(std::string a)
		{
			this->shader->RegisterAttribute(a);
			return this;
		}

		ShaderFactory* ShaderFactory::RegisterUniform(std::string u)
		{
			this->shader->RegisterUniform(u);
			return this;
		}

		ShaderFactory* ShaderFactory::RegisterTexture(std::string u, int i)
		{
			this->shader->RegisterTexture(u, i);
			return this;
		}
	}
}