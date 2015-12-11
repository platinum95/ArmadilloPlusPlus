#include "VertexBuffer.h"
#include "GL\glew.h"
namespace Armadillo
{
	namespace Graphics
	{
		VertexBuffer::VertexBuffer()
		{
			GLuint id;
			glGenVertexArrays(1, &id);
			this->Id = id;
			this->Vbo = std::vector<int>();
			this->Length = 0;
		}

		VertexBuffer::VertexBuffer(Model* data, int hint)
		{			
			GLuint id;
			glGenVertexArrays(1, &id);
			this->Id = id;
			this->Vbo = std::vector<int>();
			this->GenBuffers(3);
			this->BufferData(data->Positions, data->Normals, data->TextureCoords, data->LengthData, hint);
		}

		void VertexBuffer::GenBuffers(int count)
		{
			GLuint* vbo = new GLuint[count];
			glBindVertexArray(this->Id);
			glGenBuffers(count, vbo);
			for (int i = 0; i < count; i++)
				this->AddVbo(vbo[i]);
			delete[] vbo;
		}

		void VertexBuffer::BufferData(int attrib, int dim, float* data, int count, int hint)
		{
			glBindVertexArray(this->Id);
			glBindBuffer(GL_ARRAY_BUFFER, this->Vbo[attrib]);
			glBufferData(GL_ARRAY_BUFFER, count * dim * sizeof(float), data, hint);
			glVertexAttribPointer(attrib, dim, GL_FLOAT, GL_FALSE, 0, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void VertexBuffer::BufferData(float* p, float* n, float* t, int count, int hint)
		{
			this->BufferData(0, 3, p, count, hint);
			this->BufferData(1, 3, n, count, hint);
			this->BufferData(2, 2, t, count, hint);
		}

		void VertexBuffer::AddVbo(int i)
		{
			this->Vbo.push_back(i);
			this->Length++;
		}

		void VertexBuffer::Bind()
		{
			glBindVertexArray(this->Id);
			for (int i = 0; i < this->Length; i++)
				glEnableVertexAttribArray(i);
		}

		void VertexBuffer::Dispose()
		{
			for (GLuint i : this->Vbo)
				glDeleteBuffers(1, &i);
			GLuint id = this->Id;
			glDeleteVertexArrays(1, &id);
		}	

		void VertexBuffer::Render(int type, IndexBuffer buffer)
		{
			buffer.Bind();
			glDrawElements(type, buffer.Count, buffer.Type, 0);
		}

		void VertexBuffer::Render(int type)
		{
			glDrawArrays(type, 0, this->Count);
		}

		VertexBuffer::~VertexBuffer()
		{

		}

		void VertexBuffer::Unbind()
		{
			for (int i = 0; i < this->Length; i++)
				glDisableVertexAttribArray(i);			
			glBindVertexArray(0);
		}
	}
}
