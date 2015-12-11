#pragma once
#include <map>
#include <fstream>
#include "Character.h"

namespace Armadillo
{
	namespace Font
	{
		enum PadDirection
		{
			PadTop = 0,
			PadLeft = 1,
			PadBottom = 2,
			PadRight = 3
		};

		class FontFile
		{
		private:
			//Constants
			const int DesiredPadding = 3;
			const char Splitter = ' ';
			const char Separator = ',';
			const int SpaceAscii = 32;
			const double LineHeight = 0.03f;

			//Attributes
			std::map<int, Character> metaData;
			std::map<std::string, std::string> values;
			std::ifstream stream;

			double verticalPerPixelSize;
			double horizontalPerPixelSize;
			double spaceWidth;
			int* padding;
			int paddingWidth;
			int paddingHeight;

			//Private Methods
			void OpenFile(std::string);
			void LoadPaddingData();
			void LoadLineSizes();
			void LoadCharacterData(int);
			Character* LoadCharacter(int);
			void Close();
			bool ProcessNextLine();
			int GetValue(std::string);
			int* GetValues(std::string);
		public:

			//Constructors
			FontFile(std::string);

			Character& GetCharacter(int);
			double GetSpaceWidth();
		};
	}
}