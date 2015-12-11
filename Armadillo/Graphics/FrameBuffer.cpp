#include "FrameBuffer.h"
#include "GL\glew.h"

namespace Armadillo
{
	namespace Graphics
	{
		FrameBuffer::FrameBuffer(int i, int j)
		{
			GLuint id;
			glGenFramebuffers(1, &id);
			this->Id = id;
			glBindFramebuffer(GL_FRAMEBUFFER, id);
			glDrawBuffer(GL_COLOR_ATTACHMENT0);
			this->Width = i;
			this->Height = j;
			this->Attachments = std::vector<int>();
			this->AttachmentTypes = std::vector<AttachmentType>();
		}

		FrameBuffer::~FrameBuffer()
		{
		
		}

		void FrameBuffer::Dispose()
		{
			GLuint id = this->Id;
			glDeleteFramebuffers(1, &id);
			for (GLuint i : this->Attachments)
			{
				switch (this->AttachmentTypes[i])
				{
				case FrameTexture:				
				case FrameDepthTexture:
					glDeleteTextures(1, &i);
					break;
				case FrameDepthBuffer:
					glDeleteFramebuffers(1, &i);
					break;
				}
			}
			this->Attachments.clear();
		}

		void FrameBuffer::AddTextureAttachment()
		{
			GLuint id;
			glGenTextures(1, &id);
			this->Attachments.push_back(id);
			this->AttachmentTypes.push_back(FrameTexture);
			glBindTexture(GL_TEXTURE_2D, id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, id, 0);
		}

		void FrameBuffer::AddTextureAttachment(int i)
		{
			
		}

		void FrameBuffer::AddDepthTextureAttachment()
		{
			GLuint id;
			glGenTextures(1, &id);
			this->Attachments.push_back(id);
			this->AttachmentTypes.push_back(FrameDepthTexture);
			glBindTexture(GL_TEXTURE_2D, id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, Width, Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_NONE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, id, 0);
		}

		void FrameBuffer::AddDepthBufferAttachment()
		{
			GLuint id;
			glGenRenderbuffers(1, &id);
			this->Attachments.push_back(id);
			this->AttachmentTypes.push_back(FrameDepthBuffer);
			glBindRenderbuffer(GL_RENDERBUFFER, id);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, Width, Height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, id);
		}

		void FrameBuffer::Bind()
		{
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindFramebuffer(GL_FRAMEBUFFER, this->Id);
		}

		void FrameBuffer::Unbind()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}