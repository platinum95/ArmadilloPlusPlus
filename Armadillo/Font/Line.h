#pragma once
#include "Word.h"

namespace Armadillo
{
	namespace Font
	{
		class Line
		{
		private:
			double maxLength;
			double spaceSize;

			double currentLength;
			std::vector<Word*> words;
		public:

			Line(double, double, double);
			~Line();
			
			bool AddWord(Word*);
			double GetMaxLength();
			double GetLineLength();
			std::vector<Word*>& GetWords();
		};
	}
}