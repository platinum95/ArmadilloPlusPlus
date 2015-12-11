#pragma once
#include <vector>
#include <string>

namespace Armadillo
{
	namespace String
	{
		extern std::vector<std::string> Split(std::string s, std::string t);
		extern std::vector<std::string>& Split(const std::string &s, char delim, std::vector<std::string> &elems);
		extern std::vector<std::string> Split(const std::string &s, char delim);
		extern std::string RemoveWhiteSpace(std::string s);
		extern bool IsWhiteSpace(std::string s);
	}
}