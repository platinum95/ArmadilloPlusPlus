#include "EntityControl.h"
#include "Logger.h"

#include "../World/Entity.h"
#include "../World/EntityTypes.h"
#include "../Maths/StringHelper.h"
#include "../Osiris.h"

#include <fstream>
#include <sstream>
#include <algorithm>

namespace Armadillo
{
	namespace Management
	{
		using namespace Armadillo::World;
		using namespace std;

		EntityControl::EntityControl()
		{
			this->Entities = std::vector<Entity*>();
			this->Length = 0;
			this->Index = -1;
			this->FermatIndex = -1;
			this->IsLoaded = false;
			this->HasSpawnable = false;
		}
		
		EntityControl::~EntityControl()
		{

		}

		Entity* EntityControl::Spawnable()
		{
			return this->HasSpawnable ? this->Entities[this->Index] : NULL;
		}

		void EntityControl::SetEntityTypes(EntityTypes* et)
		{
			this->types = et;
		}

		void EntityControl::CreateSpawnable()
		{
			if (!this->HasSpawnable)
			{
				this->HasSpawnable = true;
				this->Index = this->Entities.size() - 1;
				return;
			}

			if (this->IsLoaded)
			{
				this->Entities.push_back(new Entity(Maths::Vector3(0, 0, 0), Maths::Vector3(0, 0, 0), 1.0f, this->types->GetKey(this->FermatIndex)));
				this->Index = this->Entities.size() - 1;
			}			
		}

		void EntityControl::Spawn(Entity* e)
		{
			this->Entities.push_back(e);
			this->Length++;
		}

		void EntityControl::Spawn(Maths::Vector3 pos, Maths::Vector3 rot, float size, int fermat)
		{
			this->Entities.push_back(new Entity(pos, rot, size, this->types->GetKey(this->FermatIndex)));
			this->Length++;
		}		

		int GetIndexOfFermat(std::vector<Graphics::Fermat> fermats,  Graphics::Fermat match)
		{
			int i = 0;
			for (Graphics::Fermat f : fermats)
			{
				if (f == match)
					return i;
			}
			return i;
		}

		void EntityControl::Save()
		{
			std::ofstream stream(Osiris::FileEntities);

			Management::Logger::Print("Saving Entities...");

			std::string line = "";
			int i = 0;

			for (Entity* e : this->Entities)
				stream << "e:"
				<< e->Position.x << "," << e->Position.y << "," << e->Position.z << ","
				<< e->Rotation.x << "," << e->Rotation.y << "," << e->Rotation.z << ","
				<< e->Scale << "," << e->Type << ";" << std::endl;
			stream.close();
		}

		void EntityControl::Load()
		{
			std::ifstream stream(Osiris::FileEntities);

			Management::Logger::Print("Loading Entities...");
			std::string line = "";
			while (!stream.eof())
			{
				std::getline(stream, line);
				if (line[0] == 'e')
				{
					int i = line.find(':') + 1;
					std::string lineRemoved = String::RemoveWhiteSpace(line.substr(i, line.size() - i - 1));
					std::vector<std::string> parts = String::Split(lineRemoved, ',');
					if (parts.size() < 8)
						continue;
					Entity* entity = new Entity(
						Maths::Vector3(std::stof(parts[0]), std::stof(parts[1]), std::stof(parts[2])),
						Maths::Vector3(std::stof(parts[3]), std::stof(parts[4]), std::stof(parts[5])),
						std::stof(parts[6]),
						parts[7]);
					this->Spawn(entity);
				}					
			}
			stream.close();
			this->IsLoaded = true;
			this->FermatIndex = 0;
			//this->Index = 0;
		}
	}
}