#pragma once
#include <vector>
#include "TerrainManager.h"

namespace Armadillo
{
	namespace Graphics
	{
		class View;
	}
	namespace World
	{		
		class Seed;
		class Entity;
		class Light;
		class Terrain;
		class Water;

		class Landscape
		{
		private:
			//Private Attributes
			Graphics::View* view;
			Seed* seed;
			TerrainManager tManager;

		public:
			//Public Renderable Objects
			std::vector<Light*> Lights;

			//Constructor
			Landscape(Seed*, Graphics::View*);

			//World Methods
			void Gravity();
			void Generate();
			
			//Getter Methods			
			float GetHeight(float, float);
			Seed* GetSeed();
			Terrain* GetTerrainOfView();
			TerrainManager& GetTerrainManager();
		};
	}
}