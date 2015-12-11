#include "EntityList.h"


using namespace Armadillo::Physics;

namespace Armadillo {
	namespace Physics {

		EntityList::EntityList()
		{
			entityList = std::vector<PhysicsEntity*>(0);
			size = 0;
		}


		EntityList::~EntityList()
		{
		}

		void EntityList::add(PhysicsEntity* toAdd) {
			entityList.push_back(toAdd);
			size++;
		}

		void EntityList::remove(PhysicsEntity* toRemove) {

			for (int i = 0; i < size; i++) {
				if (entityList[i] == toRemove) {
					entityList.erase(entityList.begin() + i);
					size--;
				}
			}

		}

		std::vector<PhysicsEntity*> EntityList::getList() {
			return entityList;
		}

		PhysicsEntity* EntityList::at(int i) {

			if (i < 0 || i >= size)
				return NULL;

			return entityList.at(i);

		}


	}
}