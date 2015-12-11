#pragma once
#include "../Maths/VectorMath.h"
#include <vector>
#include <string>

namespace Armadillo
{
	namespace World
	{
		class Entity;
		class EntityTypes;
	}

	namespace Management
	{
		class EntityControl
		{
		private:			
			bool IsLoaded;
			bool HasSpawnable;
			World::EntityTypes* types;

		public:
			int FermatIndex;
			int Length;
			int Index;
			std::vector<World::Entity*> Entities;

			EntityControl();
			~EntityControl();

			Armadillo::World::Entity* Spawnable();
			void CreateSpawnable();
			void SetEntityTypes(World::EntityTypes*);
			void Spawn(World::Entity*);
			void Spawn(Maths::Vector3, Maths::Vector3, float, int);
			void Load();
			void Save();
		};
	}
}