#pragma once
#include "EntityList.h"
#include "../World/Landscape.h"



namespace Armadillo {
	namespace Physics {
		class PhysicsWorld
		{
		public:
			PhysicsWorld();
			PhysicsWorld(float, float);
			~PhysicsWorld();
			EntityList* entityList;
			void PhysicsWorld::addToWorld(PhysicsEntity* toAdd);
			void PhysicsWorld::removeFromWorld(PhysicsEntity* toRem);
			void PhysicsWorld::update();
			void PhysicsWorld::update(float _timeDiff);
			Armadillo::World::Landscape* world = NULL;

		private:
			float gravity;
			float drag_coef;
			EntityList *toAddQueue, *toRemoveQueue;
			Armadillo::Maths::Vector3 gravVector;
			float prevTime;
			void PhysicsWorld::CollisionDetection(std::vector<PhysicsEntity*> entities, int size, float timeDiff);
			bool locked;
			void lock();
			void unlock();
			void init();

		};
	}
}

