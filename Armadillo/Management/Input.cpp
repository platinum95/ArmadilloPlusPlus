#include "Input.h"
#include "../World/RayCaster.h"
#include "../World/Landscape.h"
#include "../Graphics/View.h"
#include "../Graphics/Projection.h"

namespace Armadillo
{
	namespace Management
	{
		using namespace std;
		using namespace World;

		Input::Input(World::Landscape* w, Graphics::View* v, Graphics::Projection* p)
		{
			this->buttonClickMap = map<int, int>();
			this->keyboardClickMap = map<int, int>();
			this->view = v;
			this->proj = p;
			this->world = w;
			this->Caster = new RayCaster(v, p);			
		}
		
		void Input::Update()
		{
			this->Caster->Update(curr.Position.x, curr.Position.y, this->world->GetTerrainOfView());
		}

		void Input::UpdateMouse(int x, int y)
		{
			prev.Position = curr.Position;
			curr.Position.x = (float)x;
			curr.Position.y = (float)y;
		}

		void Input::UpdateWheel(int x, int y)
		{
			prev.Wheel = curr.Wheel;
			curr.Wheel.y = y;
			curr.Wheel.x = x;
		}
	}
}
