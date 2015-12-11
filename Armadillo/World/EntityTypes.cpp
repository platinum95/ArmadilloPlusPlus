#include "EntityTypes.h"

#include "../Management/Logger.h"
#include "../Maths/StringHelper.h"
#include "../Osiris.h"

#include <fstream>

namespace Armadillo
{
	namespace World
	{
		EntityTypes::EntityTypes()
		{
			this->keys = std::vector<std::string>();
			this->types = std::map<std::string, Armadillo::Graphics::Fermat>();
			this->Length = 0;
		}

		Armadillo::Graphics::Fermat EntityTypes::GetType(std::string s)
		{
			return this->types[s];
		}

		Armadillo::Graphics::Fermat EntityTypes::GetType(int i)
		{
			return this->types[this->keys[i]];
		}

		std::string EntityTypes::GetKey(int i)
		{
			return this->keys[i];
		}

		void EntityTypes::Load()
		{
			std::ifstream stream(Osiris::FileEntityTypes);

			Armadillo::Management::Logger::Print("Loading Entities...");
			std::string line = "";
			while (!stream.eof())
			{
				std::getline(stream, line);

				if (isdigit(line[0]))
				{
					int i = line.find(':') + 1;
					std::string lineRemoved = Armadillo::String::RemoveWhiteSpace(line.substr(i, line.size() - i - 1));
					std::vector<std::string> parts = Armadillo::String::Split(lineRemoved, ',');
					if (parts.size() < 2)
						continue;
					Armadillo::Graphics::Fermat fermat = Armadillo::Graphics::Fermat(parts[1], parts[2]);
					this->types[parts[0]] = fermat;
					this->keys.push_back(parts[0]);
					this->Length++;
				}
			}
		}
	}
}