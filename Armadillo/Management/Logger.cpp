#include "Logger.h"
#include <iostream>
#include <fstream>

namespace Armadillo
{
	namespace Management
	{
		std::string Logger::output = "";

		void Logger::Print(std::string s)
		{
			std::cout << s << std::endl;
		}

		void Logger::Log(std::string s)
		{
			output += s;
		}

		void Print(std::string s[], int length)
		{
			for (int i = 0; i < length; i++)
			{
				std::cout << s[i] << std::endl;
			}
		}

		void Print(std::string s[], int length, std::string delimit)
		{
			for (int i = 0; i < length; i++)
			{
				std::cout << s[i] << delimit;
			}
			std::cout << std::endl;
		}
	}
}