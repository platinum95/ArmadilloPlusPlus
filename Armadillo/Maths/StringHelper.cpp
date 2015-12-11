#include "StringHelper.h"
#include <sstream>
#include <algorithm>

namespace Armadillo
{
	namespace String
	{
		std::vector<std::string> Split(std::string s, std::string t)
		{
			std::vector<std::string> res;
			while (1)
			{
				int pos = s.find(t);
				if (pos == -1){ res.push_back(s); break; }
				res.push_back(s.substr(0, pos));
				s = s.substr(pos + 1, s.size() - pos - 1);
			}
			return res;
		}

		std::vector<std::string>& Split(const std::string &s, char delim, std::vector<std::string> &elems)
		{
			std::stringstream ss(s);
			std::string item;
			while (std::getline(ss, item, delim))
				elems.push_back(item);

			return elems;
		}

		std::vector<std::string> Split(const std::string &s, char delim)
		{
			std::vector<std::string> elems;
			Split(s, delim, elems);
			return elems;
		}

		std::string RemoveWhiteSpace(std::string s)
		{
			std::string str = s;
			str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
			return str;
		}

		bool IsWhiteSpace(std::string s)
		{
			return s == "";
		}
	}
}