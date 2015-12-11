#pragma once
#include "Entity.h"
#include <vector>

namespace Armadillo
{
	namespace World
	{
		struct EntityLeaf
		{
			Entity* Entity;
			EntityLeaf* Parent;			
			Armadillo::Maths::Vector3* Displacement;
			Armadillo::Maths::Vector3* Rotation;

			EntityLeaf();
			Armadillo::Maths::Matrix GetMatrixProduct();
		};

		class EntityTree
		{
		public:
			std::vector<EntityLeaf*> Tree; //root at tree[0]
		
			EntityTree();
			void AddEntity(Entity*, int);
			void AddRoot(Entity*, Armadillo::Maths::Vector3*, Armadillo::Maths::Vector3*);
			void AddMatrix(Armadillo::Maths::Vector3*, Armadillo::Maths::Vector3*, int);
			void AddEntity(Entity*, Armadillo::Maths::Vector3*, Armadillo::Maths::Vector3*, int);
		};
	}
}