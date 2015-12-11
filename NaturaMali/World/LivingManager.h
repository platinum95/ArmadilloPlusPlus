#pragma once
#include "LivingEntity.h"
#include "LivingEntityTypes.h"

namespace Natura
{
	namespace World
	{
		class LivingManager
		{
		private:
			std::vector<LivingEntity*> entities;

			LivingEntityTypes types;
		public:

			LivingManager();

			void Update();
		};
	}
}