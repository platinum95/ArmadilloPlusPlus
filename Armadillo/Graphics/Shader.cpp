#include "Shader.h"
#include "GL\glew.h"
#include <fstream>
#include "ShaderLoader.h"

namespace Armadillo
{
	namespace Graphics
	{
		Shader::Shader(std::string vertex, std::string fragment)
		{
			this->hasCompiled = false;
			this->vertexLocation = vertex;
			this->fragmentLocation = fragment;
			this->attributeIndex = 0;
			this->attributeTable = std::vector<std::string>();
			this->uniformTable = std::vector<std::string>();
			this->textureTable = std::vector<std::string>();
			this->Name = "Default Shader";
		}

		Shader::~Shader()
		{
			this->Stop();
			glDetachShader(this->programId, this->vertexShaderId);
			glDetachShader(this->programId, this->fragmentShaderId);
			glDeleteShader(this->vertexShaderId);
			glDeleteShader(this->fragmentShaderId);
			glDeleteProgram(this->programId);
		}

		void Shader::Start()
		{
			glUseProgram(this->programId);
		}

		void Shader::Stop()
		{
			glUseProgram(0);
		}

		bool Shader::Compile()
		{
			this->vertexShaderId = this->LoadShader(this->vertexLocation, GL_VERTEX_SHADER);
			this->fragmentShaderId = this->LoadShader(this->fragmentLocation, GL_FRAGMENT_SHADER);
			this->programId = glCreateProgram();
			glAttachShader(this->programId, this->vertexShaderId);
			glAttachShader(this->programId, this->fragmentShaderId);
			this->BindAttributes();
			glLinkProgram(this->programId);
			glValidateProgram(this->programId);
			this->BindUniforms();
			this->hasCompiled = true;
			return this->hasCompiled;
		}

		void Shader::Dispose()
		{

		}

		void Shader::BindAttributes()
		{
			for (std::string s : this->attributeTable)
			{
				glBindAttribLocation(this->programId, this->attributeIndex++, s.c_str());
			}
		}

		void Shader::BindUniforms()
		{
			for (std::string s : this->uniformTable)
			{
				glGetUniformLocation(this->programId, s.c_str());
			}
			this->Start();
			int i = 0;
			for (std::string s : this->textureTable)
			{
				ShaderLoader::LoadInteger(this, s, i++);
			}
			this->Stop();
		}

		void Shader::RegisterAttribute(std::string s)
		{
			this->attributeTable.push_back(s);
		}

		void Shader::RegisterUniform(std::string s)
		{
			this->uniformTable.push_back(s);
		}

		void Shader::RegisterTexture(std::string s, int i)
		{
			this->textureTable.push_back(s);	
		}

		void Shader::RegisterAttribute(std::vector<std::string> v)
		{
			this->attributeTable.insert(this->attributeTable.end(), v.begin(), v.end());
		}

		void Shader::RegisterUniform(std::vector<std::string> v)
		{
			this->uniformTable.insert(this->uniformTable.end(), v.begin(), v.end());
		}

		int Shader::GetUniformLocation(std::string name)
		{
			return glGetUniformLocation(this->programId, name.c_str());
		}

		int Shader::GetAttributeLocation(std::string name)
		{
			return glGetAttribLocation(this->programId, name.c_str());
		}

		std::string Shader::ReadShader(std::string file)
		{
			std::string shader = "";
			std::ifstream stream(file);
			std::string line = "";
			while (!stream.eof()) {
				std::getline(stream, line);
				shader.append(line + "\n");
			}

			stream.close();
			return shader;
		}

		int Shader::LoadShader(std::string file, int shaderType)
		{
			int shaderId = glCreateShader(shaderType);
			std::string sFile = this->ReadShader(file);
			const char* cFile = sFile.c_str();
			glShaderSource(shaderId, 1, (const GLchar**)&cFile, NULL);
			glCompileShader(shaderId);
			GLint success;
			glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

			if (!success)
			{
				GLchar InfoLog[1024];
				glGetShaderInfoLog(shaderId, 1024, NULL, InfoLog);
				fprintf(stderr, "Error compiling Shader %d: '%s'\n", shaderType, InfoLog);
			}
			return shaderId;
		}

		int Shader::GetProgramId()
		{
			return this->programId;
		}
	}
}