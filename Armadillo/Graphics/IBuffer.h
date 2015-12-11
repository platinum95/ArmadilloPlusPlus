#pragma once
#include "../Management/IDisposable.h"

namespace Armadillo
{
	namespace Graphics
	{
		class IBuffer : public IDisposable
		{
		public:
			int Id;
			int Count;

			virtual void Bind() = 0;		
			virtual void Unbind() = 0;

			virtual ~IBuffer() { };
		};
	}
}