#include "FloatBuffer.h"
#include "GL\glew.h"

namespace Armadillo
{
	namespace Graphics
	{
		FloatBuffer::FloatBuffer()
		{
			GLuint id;
			glGenVertexArrays(1, &id);
			this->Id = id;
		}

		FloatBuffer::FloatBuffer(int size, float* data, int count, int hint)
		{
			GLuint id;
			glGenVertexArrays(1, &id);
			this->Id = id;
			this->SetData(size, data, count, hint);
		}

		void FloatBuffer::Bind()
		{
			glBindVertexArray(this->Id);
			glEnableVertexAttribArray(0);
		}

		void FloatBuffer::Dispose()
		{
			GLuint id = this->Id;
			glDeleteVertexArrays(1, &id);
		}

		void FloatBuffer::SetData(int size, float* data, int count, int hint)
		{
			this->Count = count;
			this->Bind();
			this->SetData(0, size, data, count, hint);
			this->Unbind();
		}

		void FloatBuffer::SetData(int attribute, int size, float* data, int count, int hint)
		{
			GLuint vbo;
			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, size * count * sizeof(float), data, hint);

			glVertexAttribPointer(attribute, size, GL_FLOAT, GL_FALSE, 0, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void FloatBuffer::Render(int type, int first, int count)
		{
			glDrawArrays(type, first, count);
		}

		void FloatBuffer::Render(int type)
		{
			glDrawArrays(type, 0, this->Count);
		}

		void FloatBuffer::Unbind()
		{
			glDisableVertexAttribArray(0);
		}

		FloatBuffer::~FloatBuffer()
		{
			
		}
	}
}