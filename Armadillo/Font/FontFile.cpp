#include "FontFile.h"
#include "../Maths/StringHelper.h"
#include "../Osiris.h"
#include <iostream>

namespace Armadillo
{
	namespace Font
	{
		using namespace std;
		using namespace Armadillo::String;
		using namespace Armadillo::Maths;

		FontFile::FontFile(string s)
		{
			this->metaData = map<int, Character>();
			this->values = map<string, string>();
			this->OpenFile(s);
			this->LoadPaddingData();
			this->LoadLineSizes();
			this->LoadCharacterData(GetValue("scaleW"));
			this->Close();
		}

		void FontFile::OpenFile(string s)
		{
			this->stream.open(s);
		}

		Character& FontFile::GetCharacter(int i)
		{
			return this->metaData[i];
		}

		double FontFile::GetSpaceWidth()
		{
			return this->spaceWidth;
		}

		void FontFile::LoadPaddingData()
		{
			this->ProcessNextLine();
			this->padding = this->GetValues("padding");
			this->paddingWidth = this->padding[PadLeft] + this->padding[PadRight];
			this->paddingHeight = this->padding[PadTop] + this->padding[PadBottom];
		}

		void FontFile::LoadLineSizes()
		{
			this->ProcessNextLine();
			int lineHeightPixels = this->GetValue("lineHeight") - this->paddingHeight;
			this->verticalPerPixelSize = LineHeight / (double)lineHeightPixels;
			this->horizontalPerPixelSize = this->verticalPerPixelSize / Osiris::DisplayAspectRatio;
		}

		void FontFile::LoadCharacterData(int i)
		{
			this->ProcessNextLine();
			this->ProcessNextLine();
			Character* c;
			while (this->ProcessNextLine())
			{
				c = this->LoadCharacter(i);
				if (c != NULL)
					this->metaData[c->id] = *c;
			}
		}

		Character* FontFile::LoadCharacter(int imageSize)
		{
			int id = this->GetValue("id");
			if (id == SpaceAscii)
			{
				this->spaceWidth = (this->GetValue("xadvance") - paddingWidth) * horizontalPerPixelSize;
				return NULL;
			}
			double xTex = ((double)this->GetValue("x") + (padding[PadLeft] - DesiredPadding)) / imageSize;
			double yTex = ((double)this->GetValue("y") + (padding[PadTop] - DesiredPadding)) / imageSize;
			int width = this->GetValue("width") - (paddingWidth - (2 * DesiredPadding));
			int height = this->GetValue("height") - ((paddingHeight)-(2 * DesiredPadding));
			double quadWidth = width * this->horizontalPerPixelSize;
			double quadHeight = height * this->verticalPerPixelSize;
			double xTexSize = (double)width / imageSize;
			double yTexSize = (double)height / imageSize;
			double xOff = (this->GetValue("xoffset") + padding[PadLeft] - DesiredPadding) * this->horizontalPerPixelSize;
			double yOff = (this->GetValue("yoffset") + (padding[PadTop] - DesiredPadding)) * this->verticalPerPixelSize;
			double xAdvance = (this->GetValue("xadvance") - paddingWidth) * this->horizontalPerPixelSize;
			return new Character(id, xTex, yTex, xTexSize, yTexSize, xOff, yOff, quadWidth, quadHeight, xAdvance);
		}

		void FontFile::Close()
		{
			this->stream.close();
		}

		int FontFile::GetValue(string s)
		{
			return stoi(this->values[s]);
		}

		int* FontFile::GetValues(string s)
		{
			vector<string> numbers = Split(this->values[s], Separator);
			int* values = new int[numbers.size()];
			int i = 0;
			for (string n : numbers)
				values[i++] = stoi(n);
			return values;
		}

		bool FontFile::ProcessNextLine()
		{
			this->values.clear();
			string line = "";

			getline(this->stream, line);

			if (IsWhiteSpace(line))
				return false;

			for (string part : Split(line, Splitter))
			{
				vector<string> valuePairs = Split(part, "=");
				if (valuePairs.size() == 2)
				{
					this->values[valuePairs[0]] = valuePairs[1];
				}
			}
			return true;
		}
	}
}