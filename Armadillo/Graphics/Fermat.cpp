#include "Fermat.h"

namespace Armadillo
{
	namespace Graphics
	{
		Fermat::Fermat()
		{

		}

		Fermat::~Fermat()
		{

		}

		Fermat::Fermat(std::string buffer, std::string texture)
		{
			this->Buffer = buffer;
			this->Texture = texture;
		}

		bool operator<(const Fermat& g, const Fermat& f)
		{			
			std::string sg = g.Buffer + g.Texture;
			std::string sf = f.Buffer + f.Texture;

			return sg < sf;
		}

		bool operator==(const Fermat& g, const Fermat& f)
		{
			std::string sg = g.Buffer + g.Texture;
			std::string sf = f.Buffer + f.Texture;

			return sg == sf;
		}

		bool operator>(const Fermat& g, const Fermat& f)
		{
			std::string sg = g.Buffer + g.Texture;
			std::string sf = f.Buffer + f.Texture;

			return sg > sf;
		}

		bool operator>=(const Fermat& g, const Fermat& f)
		{
			return !(g < f);
		}

		bool operator<=(const Fermat& g, const Fermat& f)
		{
			return !(g > f);
		}
	}
}