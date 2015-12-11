#pragma once
#include <string>

namespace Natura
{
	namespace World
	{
		class BaseStage
		{
		protected:
			float size;
			std::string model;
			std::string texture;

		public:
			BaseStage(float, std::string, std::string);

			float GetSize();
			std::string GetModel();
			std::string GetTexture();
		};
	}
}