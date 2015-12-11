#pragma once
#include <vector>
#include "PhysicsEntity.h"

namespace Armadillo {
	namespace Physics {

		class EntityList
		{
		public:
			EntityList();
			~EntityList();
			void EntityList::add(PhysicsEntity* toAdd);
			void EntityList::remove(PhysicsEntity*);
			std::vector<PhysicsEntity*> EntityList::getList();
			PhysicsEntity* at(int);


			int size;

		private:
			std::vector<PhysicsEntity*> entityList;
		};

	}
}