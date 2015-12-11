#include "Character.h"

namespace Armadillo
{
	namespace Font
	{
		using namespace Armadillo::Maths;

		Character::Character(int id, float xTextureCoord, float yTextureCoord, float xTexSize, float yTexSize,	float xOffset, float yOffset, float sizeX, float sizeY, float xAdvance)
		{
			this->id = id;
			this->TextureCoord = Vector2(xTextureCoord, yTextureCoord);			
			this->Offset = Vector2(xOffset, yOffset);			
			this->Size = Vector2(sizeX, sizeY);
			this->MaxTextureCoord = Vector2(xTexSize + xTextureCoord, yTexSize + yTextureCoord);
			this->Advance = xAdvance;
		}
	}
}