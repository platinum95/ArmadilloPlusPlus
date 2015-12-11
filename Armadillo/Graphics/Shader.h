#pragma once
#include <vector>
#include <string>
#include "../Management/IDisposable.h"

namespace Armadillo
{
	namespace Graphics
	{
		class Shader : public IDisposable
		{
		private:
			bool hasCompiled;
			int programId;
			int vertexShaderId;
			int fragmentShaderId;
			int attributeIndex;

			std::string vertexLocation;
			std::string fragmentLocation;

			std::vector<std::string> attributeTable;
			std::vector<std::string> uniformTable;
			std::vector<std::string> textureTable;

			std::string ReadShader(std::string);
			int LoadShader(std::string, int);

			void BindAttributes();
			void BindUniforms();
		public:
			Shader(std::string, std::string);
			~Shader();

			void Start();
			void Stop();
			bool Compile();
			void Dispose();

			void RegisterAttribute(std::string);
			void RegisterUniform(std::string);
			void RegisterTexture(std::string, int);
			void RegisterAttribute(std::vector<std::string>);			
			void RegisterUniform(std::vector<std::string>);

			std::string Name;
			int GetProgramId();
			int GetUniformLocation(std::string);
			int GetAttributeLocation(std::string);
		};
	}
}