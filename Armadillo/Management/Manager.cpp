#include "Manager.h"
#include "Logger.h"
#include "IDisposable.h"

namespace Armadillo
{
	namespace Management
	{
		Manager::Manager(std::string n)
		{
			this->Identity = n;
			this->table = std::map<std::string, IDisposable*>();
			this->size = 0;
			Logger::Print("Creating: " + this->Identity);
		}

		Manager::Manager()
		{
			this->Identity = "DefaultIdentity";
			this->table = std::map<std::string, IDisposable*>();
			this->size = 0;			
		}

		Manager::~Manager()
		{

		}

		IDisposable* Manager::Get(std::string name)
		{			
			return this->table[name];
		}

		void Manager::Register(std::string name, IDisposable* t)
		{
			Logger::Print(this->Identity + " Registering: " + name);
			this->table[name] = t;
			this->size++;
		}

		void Manager::Dispose(std::string name)
		{
			std::map<std::string, IDisposable*>::iterator itr = this->table.find(name);
			if (itr != this->table.end())
			{
				Logger::Print(this->Identity + " DeRegistering: " + name);
				IDisposable* obj = dynamic_cast<IDisposable*>(itr->second);
				if (obj != NULL)
					obj->Dispose();
				delete itr->second;
				this->table.erase(itr);
			}			
		}
	}
}
