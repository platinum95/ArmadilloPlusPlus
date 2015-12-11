#include "UniformBuffer.h"
#include "../Management/DataTypeSize.h"
#include "GL\glew.h"

namespace Armadillo
{
	namespace Graphics
	{		
		UniformBuffer::UniformBuffer(std::string s, int i, int c)
		{
			this->Count = 1;
			this->Size = c;
			this->Index = i;
			this->Binding = s;
			this->data = std::vector<float>();
			this->GenBuffer();
			this->BufferData(NULL);
		}

		UniformBuffer::~UniformBuffer()
		{

		}

		void UniformBuffer::Bind()
		{
			glBindBuffer(GL_UNIFORM_BUFFER, this->Id);
		}

		void UniformBuffer::Unbind()
		{
			glBindBuffer(GL_UNIFORM_BUFFER, 0);			
		}

		void UniformBuffer::Dispose()
		{
			GLuint id = this->Id;
			glDeleteBuffers(1, &id);
		}

		void UniformBuffer::GenBuffer()
		{
			GLuint id;
			glGenBuffers(1, &id);
			this->Id = id;
		}

		void UniformBuffer::BufferData(float* f)
		{
			this->Bind();
			glBufferData(GL_UNIFORM_BUFFER, this->Size, f, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
			glBindBufferRange(GL_UNIFORM_BUFFER, this->Index, this->Id, 0, this->Size);
		}

		void UniformBuffer::BufferData()
		{
			glBindBuffer(GL_UNIFORM_BUFFER, this->Id);
			glBufferData(GL_UNIFORM_BUFFER, this->Size, this->data.data(), GL_DYNAMIC_DRAW);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
			//glBindBufferRange(GL_UNIFORM_BUFFER, this->Index, this->Id, 0, this->Size);
			this->data.clear();
		}

		void UniformBuffer::AddData(float* f, int length)
		{
			for (int i = 0; i < length; i++)
				this->data.push_back(f[i]);
		}

		void UniformBuffer::AddData(float f)
		{
			this->data.push_back(f);
		}

		void UniformBuffer::AddData(Armadillo::Maths::Vector2 v)
		{
			this->data.push_back(v.x);
			this->data.push_back(v.y);
		}

		void UniformBuffer::AddData(Armadillo::Maths::Vector3 v)
		{
			this->data.push_back(v.x);
			this->data.push_back(v.y);
			this->data.push_back(v.z);
			this->data.push_back(0);
		}

		void UniformBuffer::AddData(Armadillo::Maths::Vector3 v, float f)
		{
			this->data.push_back(v.x);
			this->data.push_back(v.y);
			this->data.push_back(v.z);
			this->data.push_back(f);
		}

		void UniformBuffer::AddData(Armadillo::Maths::Vector4 v)
		{
			this->data.push_back(v.x);
			this->data.push_back(v.y);
			this->data.push_back(v.z);
			this->data.push_back(v.w);
		}

		void UniformBuffer::AddData(Armadillo::Maths::Matrix m)
		{
			this->AddData(m.m, 16);
		}

		void UniformBuffer::BlockBindShader(Shader* s)
		{
			glUniformBlockBinding(s->GetProgramId(), glGetUniformBlockIndex(s->GetProgramId(), this->Binding.c_str()), this->Index);
		}
	}
}