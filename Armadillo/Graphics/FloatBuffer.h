#pragma once
#include "IBuffer.h"
namespace Armadillo
{
	namespace Graphics
	{
		class FloatBuffer :
			public IBuffer
		{
		public:
			//Inheritanced
			void Bind();
			void Unbind();			
			void Dispose();

			void SetData(int, float*, int, int);
			void SetData(int, int, float*, int, int);
			void Render(int, int, int);
			void Render(int);

			FloatBuffer();
			FloatBuffer(int, float*, int, int);
			~FloatBuffer();
		};
	}
}