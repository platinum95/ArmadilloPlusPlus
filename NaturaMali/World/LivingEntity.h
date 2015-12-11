#pragma once
#include "World\Entity.h"

namespace Natura
{
	namespace World
	{
		class LivingEntity : public Armadillo::World::Entity
		{
		private:
			float age;
			int stage;
		public:
			LivingEntity(int);
			~LivingEntity();

			float GetAge();
			int GetStage();
			void Grow();
			void Grow(int);
			void Update();
		};
	}
}