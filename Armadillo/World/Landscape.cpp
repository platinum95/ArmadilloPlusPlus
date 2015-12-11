#include "Landscape.h"
#include "Light.h"
#include "Entity.h"
#include "Water.h"
#include "Terrain.h"

#include "../Osiris.h"
#include "../Graphics/View.h"

#include <algorithm>
#include <thread>
#include <random>

namespace Armadillo
{
	namespace World
	{
		using namespace Armadillo::Graphics;
		using namespace std;

		Landscape::Landscape(Seed* s, View* v)
		{
			this->view = v;
			this->seed = s;
			this->tManager = TerrainManager(s, v);
			this->Lights = vector<Light*>();			
			this->Generate();
		}

		void Landscape::Gravity()
		{
			if (Osiris::WorldGravityEnable)
			{
				this->view->Position.y -= Osiris::WorldGravity / 32;
				float f = this->GetHeight(this->view->Position.x, this->view->Position.z) + Osiris::PlayerHeight;
				if (this->view->Position.y < f)
					this->view->Position.y = f;
			}
		}

		void Landscape::Generate()
		{
			this->tManager.Generate();
		}

		float Landscape::GetHeight(float x, float z)
		{
			return this->tManager.GetHeight(x, z);
		}

		Seed* Landscape::GetSeed()
		{
			return this->seed;
		}

		Terrain* Landscape::GetTerrainOfView()
		{
			return this->tManager.GetTerrain(this->view->Position.x, this->view->Position.z);
		}

		TerrainManager& Landscape::GetTerrainManager()
		{
			return this->tManager;
		}
	}
}