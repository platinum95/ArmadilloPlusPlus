#pragma once
#include "../Maths/VectorMath.h"
#include "../Graphics/Fermat.h"

namespace Armadillo
{
	namespace World
	{
		class Entity
		{
		public:			
			float ShineDamper;
			float Reflectivity;
			Armadillo::Maths::Vector3 Position;
			Armadillo::Maths::Vector3 Rotation;
			float Scale;
			std::string Type;
			Armadillo::Maths::Vector3 TextureData;
		
			Entity();
			~Entity();
			Entity(Armadillo::Maths::Vector3, Armadillo::Maths::Vector3, float, Armadillo::Maths::Vector3, float, float, std::string);
			Entity(Armadillo::Maths::Vector3, Armadillo::Maths::Vector3, float, std::string);
			Entity(Armadillo::Maths::Vector3, Armadillo::Maths::Vector3, float);
		};
	}
}
