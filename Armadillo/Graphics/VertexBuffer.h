#pragma once
#include <vector>
#include "IBuffer.h"
#include "IndexBuffer.h"
#include "ModelData.h"

namespace Armadillo
{
	namespace Graphics
	{
		class VertexBuffer : public IBuffer
		{
		private:
			void AddVbo(int);
		public:
			std::vector<int> Vbo;
			int Length;

			//Inheritanced
			void Bind();
			void Unbind();
			void Dispose();

			//Public Render
			void Render(int, IndexBuffer);
			void Render(int);

			//Public Data Set
			void GenBuffers(int);
			void BufferData(int, int, float*, int, int);
			void BufferData(float*, float*, float*, int, int);

			//Constructors
			VertexBuffer();
			VertexBuffer(Model*, int);
			~VertexBuffer();
		};
	}
}

