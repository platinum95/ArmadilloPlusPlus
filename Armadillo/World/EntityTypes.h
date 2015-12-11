#pragma once
#include <map>
#include <string>
#include <vector>
#include "../Graphics/Fermat.h"

namespace Armadillo
{
	namespace World
	{
		class EntityTypes
		{
		private:
			std::map<std::string, Graphics::Fermat> types;
			std::vector<std::string> keys;			

		public:
			int Length;

			EntityTypes();

			void Load();
			Graphics::Fermat GetType(std::string);
			Graphics::Fermat GetType(int);
			std::string GetKey(int);
		};
	}
}