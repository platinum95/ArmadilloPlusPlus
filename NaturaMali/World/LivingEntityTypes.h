#pragma once
#include <string>
#include <map>
#include <vector>
#include "BaseStage.h"

namespace Natura
{
	namespace World
	{
		class LivingEntityTypes
		{
		private:
			std::map<std::string, std::vector<BaseStage>> entityMap;

			void AddStage(float, std::string, std::string);
		public:
			LivingEntityTypes(std::string);

			BaseStage GetStage(std::string, int);
		};
	}
}