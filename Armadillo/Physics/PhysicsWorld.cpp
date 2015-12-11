#include "PhysicsWorld.h"
#include "../Osiris.h"
#include "PhysicsConstants.h"

namespace Armadillo {
	namespace Physics {
		PhysicsWorld::PhysicsWorld() {
			gravity = 9.81f;

			init();
		}


		PhysicsWorld::~PhysicsWorld() {
			delete entityList;
		}
		PhysicsWorld::PhysicsWorld(float grav, float drag) {		
			PhysicsConstants::gravity = grav;		
			PhysicsConstants::drag_coef = drag;

			init();
		}
		void PhysicsWorld::init() {
			entityList = new EntityList;
			prevTime = 0;
			gravVector = Armadillo::Maths::Vector3(0, gravity, 0);
			toAddQueue = new EntityList();
			toRemoveQueue = new EntityList();
			locked = false;
			
		}

		void PhysicsWorld::addToWorld(PhysicsEntity* toAdd) {
			if(!locked)
				entityList->add(toAdd);

			else {
				toAddQueue->add(toAdd);
			}
		}

		void PhysicsWorld::removeFromWorld(PhysicsEntity* toRem) {
			if (!locked)	
				entityList->remove(toRem);

			else {
				toRemoveQueue->add(toRem);
			}
		}
		void PhysicsWorld::lock() {
			locked = true;
		}

		void PhysicsWorld::unlock() {
			int addSize = toAddQueue->size, remSize = toRemoveQueue->size;

			if (addSize != 0) {
				for (int i = 0; i < addSize; i++) {
					entityList->add(toAddQueue->at(i));
				}
			}
			if (remSize != 0) {
				for (int i = 0; i < addSize; i++) {
					entityList->remove(toRemoveQueue->at(i));
				}
			}

			locked = false;
		}

		void PhysicsWorld::update(float _timeDiff) {
			lock();
			std::vector<PhysicsEntity*> entities = entityList->getList();
			int size = entities.size();
			

			CollisionDetection(entities, size, _timeDiff);
			
			

			unlock();
		}

		void PhysicsWorld::CollisionDetection(std::vector<PhysicsEntity*> entities, int size, float timeDiff) {
			EntityList checkedVectors;
			for (int i = 0; i < size; i++) {
				PhysicsEntity* currentEntity = entities.at(i);

				currentEntity->update(checkedVectors.getList(), timeDiff);
				

				checkedVectors.add(currentEntity);
			}
		}
	}
}