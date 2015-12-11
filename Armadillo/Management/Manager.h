#pragma once
#include <map>
#include <string>
#include "IDisposable.h"

namespace Armadillo
{
	namespace Management
	{		
		class Manager
		{
		private:
			std::map<std::string, IDisposable*> table;
			int size;			
		
		public:
			std::string Identity;

			IDisposable* Get(std::string);
			
			Manager();
			Manager(std::string);
			~Manager();
			
			void Register(std::string, IDisposable*);
			void Dispose(std::string);
		};		
	}
}
