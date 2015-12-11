#pragma once
#include "IBuffer.h"
#include "Shader.h"

#include "../Maths/VectorMath.h"

namespace Armadillo
{
	namespace Graphics
	{	

		class UniformBuffer : public IBuffer
		{
		private:
			std::vector<float> data;
		public:
			//Public Attributes
			int Size;
			int Index;
			std::string Binding;

			//Inheritanced
			void Bind();
			void Unbind();
			void Dispose();

			void GenBuffer();
			void BufferData(float*);
			void AddData(float*, int);
			void AddData(float);
			void AddData(Armadillo::Maths::Vector2);
			void AddData(Armadillo::Maths::Vector3);
			void AddData(Armadillo::Maths::Vector3, float);
			void AddData(Armadillo::Maths::Vector4);
			void AddData(Armadillo::Maths::Matrix);
			void BlockBindShader(Shader*);
			void BufferData();

			//Constructors
			UniformBuffer(std::string, int, int);
			~UniformBuffer();
		};
	}
}