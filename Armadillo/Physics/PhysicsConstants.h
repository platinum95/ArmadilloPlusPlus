#pragma once

#include "../World/Landscape.h"

namespace Armadillo {
	namespace Physics {
		class PhysicsConstants
		{
		public:
			static float gravity;
			static float drag_coef;
			static Armadillo::World::Landscape* world;
			static float he;

			static void setWorld(Armadillo::World::Landscape* _world);

		};

	}
}

