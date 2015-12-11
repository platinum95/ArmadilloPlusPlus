#pragma once
#include <string>

namespace Armadillo
{
	namespace Graphics
	{
		class Fermat
		{
		public:
			std::string Buffer;
			std::string Texture;
			
			Fermat();
			Fermat(std::string, std::string);
			~Fermat();

			friend bool operator <(const Fermat&, const Fermat&);
			friend bool operator ==(const Fermat&, const Fermat&);
			friend bool operator >(const Fermat&, const Fermat&);
			friend bool operator >=(const Fermat&, const Fermat&);
			friend bool operator <=(const Fermat&, const Fermat&);

			
		};
	}
}
