#include "PhysicsConstants.h"

using namespace Armadillo;


namespace Armadillo {
	namespace Physics {


		World::Landscape* PhysicsConstants::world = NULL;
		float PhysicsConstants::gravity;
		float PhysicsConstants::drag_coef;

		void PhysicsConstants::setWorld(Armadillo::World::Landscape* _world){
			world = _world;
		}

	}
}
