#include "IndexBuffer.h"
#include "GL\glew.h"
namespace Armadillo
{
	namespace Graphics
	{
		IndexBuffer::IndexBuffer(int type)
		{
			this->Type = type;
			GLuint id;
			glGenBuffers(1, &id);
			this->Id = id;
		}

		IndexBuffer::IndexBuffer(Model* data, int hint, int type)
		{			
			this->Type = type;
			GLuint id;
			glGenBuffers(1, &id);
			this->Id = id;
			this->SetData(data->Indices, data->LengthIndex, hint);
		}

		IndexBuffer::~IndexBuffer()
		{

		}

		void IndexBuffer::Dispose()
		{
			GLuint id = this->Id;
			glDeleteBuffers(1, &id);
		}

		void IndexBuffer::Bind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->Id);
		}

		void IndexBuffer::SetData(int* data, int count, int hint)
		{
			this->Count = count;
			this->Bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * GetSizeInBytes(), data, hint);
		}

		int IndexBuffer::GetSizeInBytes()
		{
			switch (Type)
			{
			case GL_UNSIGNED_BYTE:
				return 1;
			case GL_UNSIGNED_SHORT:
				return 2;
			case GL_UNSIGNED_INT:
				return 4;
			default:
				return 0;
			}
		}

		void IndexBuffer::Unbind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}