#pragma once
#include <vector>
#include "IBuffer.h"
#include "ModelData.h"
namespace Armadillo
{
	namespace Graphics
	{
		class IndexBuffer :
			public IBuffer
		{
		public:
			int Type;

			//Inheritanced
			void Bind();
			void Unbind();
			void Dispose();

			//Members
			void SetData(int*, int, int);
			int GetSizeInBytes();

			IndexBuffer(int);
			IndexBuffer(Model*, int, int);
			~IndexBuffer();
		};
	}
}

