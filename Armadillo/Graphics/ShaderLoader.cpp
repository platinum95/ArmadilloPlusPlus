#include "ShaderLoader.h"
#include "GL\glew.h"

namespace Armadillo
{
	namespace Graphics
	{
		void ShaderLoader::LoadFloat(Shader* shader, std::string location, float value)
		{
			glUniform1f(shader->GetUniformLocation(location), value);
		}

		void ShaderLoader::LoadInteger(Shader* shader, std::string location, int value)
		{
			glUniform1i(shader->GetUniformLocation(location), value);
		}

		void ShaderLoader::LoadBoolean(Shader* shader, std::string location, bool value)
		{
			float f = (value) ? 1.0f : 0.0f;
			glUniform1f(shader->GetUniformLocation(location), f);
		}

		void ShaderLoader::LoadVector(Shader* shader, std::string location, Armadillo::Maths::Vector2 value)
		{
			glUniform2f(shader->GetUniformLocation(location), value.x, value.y);
		}

		void ShaderLoader::LoadVector(Shader* shader, std::string location, Armadillo::Maths::Vector3 value)
		{
			glUniform3f(shader->GetUniformLocation(location), value.x, value.y, value.z);
		}

		void ShaderLoader::LoadVector(Shader* shader, std::string location, Armadillo::Maths::Vector4 value)
		{
			glUniform4f(shader->GetUniformLocation(location), value.x, value.y, value.z, value.w);			
		}

		void ShaderLoader::LoadVectorArray(Shader* shader, std::string location, Armadillo::Maths::Vector4 vectors[], int size)
		{
			glUniform4fv(shader->GetUniformLocation(location), size, &vectors[0].x);
		}

		void ShaderLoader::LoadMatrix(Shader* shader, std::string location, Armadillo::Maths::Matrix value, bool transpose)
		{
			glUniformMatrix4fv(shader->GetUniformLocation(location), 1, transpose, &value.m[0]);
		}		
	}
}
