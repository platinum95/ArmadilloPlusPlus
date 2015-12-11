#include "PhysicsEntity.h"
#include "PhysicsConstants.h"
#include "../Osiris.h"

using namespace Armadillo::Maths;

namespace Armadillo {
	namespace Physics {

		PhysicsEntity::PhysicsEntity(Armadillo::Maths::Vector3 pos, Armadillo::Maths::Vector3 rot, float fl) : Armadillo::World::Entity(pos, rot, fl) {
			velocity = Armadillo::Maths::Vector3(0, 0, 0);
			position = Armadillo::Maths::Vector3(0, 0, 0);
			forces = Armadillo::Maths::Vector3(0, 0, 0);
			rotation = Armadillo::Maths::Vector3(0, 0, 0);
			mass = 20;
		}

		PhysicsEntity::PhysicsEntity(Armadillo::Maths::Vector3 pos, Armadillo::Maths::Vector3 rot) : Armadillo::World::Entity(pos, rot, 1.0f) {
			velocity = Armadillo::Maths::Vector3(0, 0, 0);
			position = Armadillo::Maths::Vector3(0, 0, 0);
			forces = Armadillo::Maths::Vector3(0, 0, 0);
			rotation = Armadillo::Maths::Vector3(0, 0, 0);
			mass = 20;
		}

		void PhysicsEntity::addForce(Armadillo::Maths::Vector3 _forces) {
			this->forces += _forces;
		}

		PhysicsEntity::PhysicsEntity(int i){
		}

		void PhysicsEntity::update(std::vector<PhysicsEntity*> eList, float) {

		}


		
		void StaticEntity::update(std::vector<PhysicsEntity*> eList, float timeDiff) {



		}





		DynamicEntity::DynamicEntity(Armadillo::Maths::Vector3 pos, Armadillo::Maths::Vector3 rot) : Armadillo::Physics::PhysicsEntity(pos, rot) {
			velocity = Armadillo::Maths::Vector3(0, 0, 0);
			position = Armadillo::Maths::Vector3(0, 0, 0);
			forces = Armadillo::Maths::Vector3(0, 0, 0);
			rotation = Armadillo::Maths::Vector3(0, 0, 0);
			mass = 20;
		}


		void DynamicEntity::update(std::vector<PhysicsEntity*> eList, float timeDiff) {
			//Add gravity vector
			this->addForce(Armadillo::Maths::Vector3(0, (PhysicsConstants::gravity * this->mass), 0));

			//Get and store the current speed
			float currentSpeed = Armadillo::Maths::Vector3::Length(this->velocity);

			//Do wind resistance stuff
			Armadillo::Maths::Vector3 windVelocityUnit = this->velocity.Negate(this->velocity);
			Armadillo::Maths::Vector3 windVelocity;

			if (currentSpeed > 0.5)
				windVelocity = Armadillo::Maths::Vector3::squareKeepSign(windVelocityUnit) * PhysicsConstants::drag_coef;
			else if (currentSpeed > 0.01)
				windVelocity = windVelocityUnit * PhysicsConstants::drag_coef;
			else
				windVelocity = Armadillo::Maths::Vector3(0, 0, 0);

			//Calculate accelerations
			Armadillo::Maths::Vector3 accelerations = this->forces * (1 / this->mass);
			
			//Get the new velocity from accelerations and wind
			this->velocity += (accelerations * timeDiff);
			this->velocity += windVelocity;

			//Get the new position
			this->position += (this->velocity * timeDiff);

			if (this->position.y < PhysicsConstants::world->GetHeight(this->position.x, this->position.z)) {
				this->velocity.y = 0;
				this->position.y = PhysicsConstants::world->GetHeight(this->position.x, this->position.z);

			}

			//Reset the force vector
			this->forces = Armadillo::Maths::Vector3(0, 0, 0);

		}
		

	}
}
