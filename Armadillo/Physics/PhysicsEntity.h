#pragma once
#include "../Maths/VectorMath.h"
#include "../World/Entity.h"
#include "../Graphics/View.h"
#include <vector>
#include "../World/Landscape.h"


namespace Armadillo{
	namespace Physics {

		class PhysicsEntity : public Armadillo::World::Entity
		{
		public:
			PhysicsEntity(Armadillo::Maths::Vector3, Armadillo::Maths::Vector3, float);
			PhysicsEntity(Armadillo::Maths::Vector3 pos, Armadillo::Maths::Vector3 rot);
			PhysicsEntity(int i);

			void addForce(Armadillo::Maths::Vector3);
			virtual void update(std::vector<PhysicsEntity*> eList, float);
			float mass, restitution, friction;
			Armadillo::Maths::Vector3 velocity, forces, position, rotation;
		};
		
		class StaticEntity : public PhysicsEntity {

		public:
			void update(std::vector<PhysicsEntity*> eList, float);

		private:

		};

		class DynamicEntity : public PhysicsEntity {

		public:
			DynamicEntity(Armadillo::Maths::Vector3 pos, Armadillo::Maths::Vector3 rot);

			void update(std::vector<PhysicsEntity*> eList, float);
		private:

		};
		
	}
}

