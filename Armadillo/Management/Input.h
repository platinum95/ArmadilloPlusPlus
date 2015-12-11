#pragma once
#include <map>
#include "../Maths/VectorMath.h"

namespace Armadillo
{
	namespace Graphics
	{
		class View;
		class Projection;
	}

	namespace World
	{
		class RayCaster;
		class Landscape;
	}

	namespace Management
	{
		struct Mouse
		{
			Maths::Vector2 Position;
			Maths::Vector2 Wheel;
		};

		class Input
		{
		protected:
			Mouse curr;
			Mouse prev;

			std::map<int, int> buttonClickMap;
			std::map<int, int> keyboardClickMap;

			Graphics::View* view;
			Graphics::Projection* proj;
			World::Landscape* world;

			virtual void UpdateMouse(int, int);
			virtual void UpdateWheel(int, int);
		public:
			World::RayCaster* Caster;

			Input(World::Landscape*, Graphics::View*, Graphics::Projection*);
			virtual ~Input() { }

			virtual bool KeyboardPress(int, int) = 0;
			virtual bool ButtonPress(int, int) = 0;

			virtual void Update();
		};
	}
}



