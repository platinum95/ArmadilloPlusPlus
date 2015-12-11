#pragma once
#include <string>
#include <sstream>

namespace Armadillo
{
	namespace Management
	{
		class Logger
		{
		private:
			static std::string output;
		public:
			static void Log(std::string);
			static void Print(std::string);
			static void Print(std::string[], int);
			static void Print(std::string[], int, std::string);
		};
	}
}
