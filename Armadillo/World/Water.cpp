#include "Water.h"
#include "GL\glew.h"
#include "../Graphics/Colour.h"

namespace Armadillo
{
	namespace World
	{
		using namespace Armadillo::Maths;
		using namespace Armadillo::Colour;
		using namespace Armadillo::Graphics;
		using namespace std;

		Water::Water(Vector3 pos, float s)
		{
			this->Position = pos;
			this->Colour = WaterBlue;
			this->Scale = s;
		}

		Water::Water(Vector3 pos, Vector3 c, float s)
		{
			this->Position = pos;
			this->Colour = c;
			this->Scale = s;
		}

		Water::~Water()
		{

		}

		FrameBuffer* Water::ReflectionBuffer(int Width, int Height)
		{
			FrameBuffer* reflection = new FrameBuffer(Width, Height);

			reflection->AddTextureAttachment();
			reflection->AddDepthBufferAttachment();
			reflection->Unbind();
			return reflection;
		}

		FrameBuffer* Water::RefractionBuffer(int Width, int Height)
		{
			FrameBuffer* refraction = new FrameBuffer(Width, Height);

			refraction->AddTextureAttachment();
			refraction->AddDepthTextureAttachment();
			refraction->Unbind();
			return refraction;
		}


		FloatBuffer* Water::QuadBuffer()
		{
			float quadArray[12] = {
				-1, -1, -1, 1,
				1, -1, 1, -1,
				-1, 1, 1, 1};
			return new FloatBuffer(2, quadArray, 6, GL_STATIC_DRAW);
		}
	}
}