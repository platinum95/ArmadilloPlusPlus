#pragma once
#include <vector>
#include "Character.h"

namespace Armadillo
{
	namespace Font
	{
		class Word
		{
		private:
			std::vector<Character*> characters;

			double width;
			double fontSize;
		public:

			Word(double);
			~Word();

			void AddCharacter(Character*);
			std::vector<Character*> GetWord();
			double GetWordWidth();
		};
	}
}