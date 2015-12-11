#pragma once
#include "IBuffer.h"
#include <vector>

namespace Armadillo
{
	namespace Graphics
	{
		enum AttachmentType
		{
			FrameTexture,
			FrameDepthBuffer,
			FrameDepthTexture
		};

		class FrameBuffer : public IBuffer
		{
		public:
			//Inheritanced
			void Bind();
			void Unbind();
			void Dispose();

			int Width, Height;

			std::vector<int> Attachments;
			std::vector<AttachmentType> AttachmentTypes;

			void AddTextureAttachment();
			void AddTextureAttachment(int);
			void AddDepthTextureAttachment();
			void AddDepthBufferAttachment();
			
			FrameBuffer(int, int);
			~FrameBuffer();
		};
	}
}