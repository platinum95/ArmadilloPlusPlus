#include "Entity.h"

namespace Armadillo
{
	namespace World
	{
		Entity::Entity()
		{
			Entity::Entity(Armadillo::Maths::Vector3(), Armadillo::Maths::Vector3(), 1.0f, Armadillo::Maths::Vector3(0, 0, 1), 1.0f, 0.0f, "");
		}

		Entity::~Entity()
		{

		}

		Entity::Entity(Armadillo::Maths::Vector3 pos, Armadillo::Maths::Vector3 rot, float scale, Armadillo::Maths::Vector3 offset, float shine, float reflect, std::string type)
		{
			this->Position = pos;
			this->Rotation = rot;
			this->Scale = scale;
			this->Type = type;
			this->ShineDamper = shine;
			this->Reflectivity = reflect;
			this->TextureData = offset;
		}

		Entity::Entity(Armadillo::Maths::Vector3 pos, Armadillo::Maths::Vector3 rot, float scale, std::string type)
		{
			this->Position = pos;
			this->Rotation = rot;
			this->Scale = scale;
			this->Type = type;
			this->ShineDamper = 1.0f;
			this->Reflectivity = 0.0f;
			this->TextureData = Armadillo::Maths::Vector3(0, 0, 1);
		}

		Entity::Entity(Armadillo::Maths::Vector3 pos, Armadillo::Maths::Vector3 rot, float scale)
		{
			Entity::Entity(pos, rot, scale, "");
		}
	}
}