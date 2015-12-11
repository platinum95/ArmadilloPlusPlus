#pragma once
#include "../Maths/VectorMath.h"

namespace Armadillo
{
	namespace Graphics
	{
		class Projection;
		class View;
	}

	namespace World
	{
		class Terrain;

		class RayCaster
		{
		private:			
			Graphics::View* view;
			Graphics::Projection* projection;
			World::Terrain* terrain;
			Maths::Vector3* PointOnRay;

			Maths::Vector4 ToEyeCoords(Maths::Vector4);
			Maths::Vector3 ToWorldCoords(Maths::Vector4);
			Maths::Vector3 GetPointOnRay(Maths::Vector3*, float);
			Maths::Vector3* BinarySearch(int, float, float, Maths::Vector3*);
			bool IntersectionInRange(float, float, Maths::Vector3*);
			bool IsUnderTerrain(Maths::Vector3);
		public:
			Maths::Vector3* Ray;
			Maths::Vector3* WorldPoint;

			RayCaster(Graphics::View*, Graphics::Projection*);
			~RayCaster();

			void Update(int, int, World::Terrain*);

			Maths::Vector3* GetWorldPoint(World::Terrain*);
			Maths::Vector3* GetRay(int, int);
			Graphics::View* GetView();			
		};
	}
}