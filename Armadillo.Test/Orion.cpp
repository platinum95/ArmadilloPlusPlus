#include "GLFW/glfw3.h"
#include "Orion.h"
#include "Osiris.h"

#include "Graphics\View.h"
#include "Graphics\Projection.h"
#include "World\Landscape.h"

#include <cmath>
#include <iostream>
#include <thread>

namespace Armadillo
{
	namespace Management
	{
		using namespace Maths;
		using namespace World;
		using namespace Graphics;
		using namespace std;

		Orion::Orion(GLFWwindow* w, World::Landscape* l, Graphics::View* v, Graphics::Projection* p) : Input(l, v, p)
		{
			this->window = w;
		}

		Orion::~Orion()
		{

		}

		void Orion::CalculatePitch()
		{
			if (ButtonPress(GLFW_MOUSE_BUTTON_1, GLFW_PRESS))
			{
				this->view->Rotation.x -= this->MouseDy() * Osiris::PlayerCameraSensitivity;
			}
		}

		void Orion::CalculateYaw()
		{
			if (ButtonPress(GLFW_MOUSE_BUTTON_1, GLFW_PRESS))
			{			
				view->Rotation.y += this->MouseDx() * Osiris::PlayerCameraSensitivity;
			}
		}

		void Orion::CalculateZoom()
		{
			float change = MouseWheelDy() * 0.1f;
			Orion::zoom -= change;
		}

		void Orion::Calculate()
		{			
			CalculatePitch();
			CalculateYaw();
		}

		double Orion::MouseDx()
		{
			float f = prev.Position.x - curr.Position.x;		
			return abs(f) > 0.001f ? f : 0;
		}

		double Orion::MouseDy()
		{
			float f = prev.Position.y - curr.Position.y;
			return abs(f) > 0.001f ? f : 0;
		}

		double Orion::MouseX()
		{
			return curr.Position.x;
		}

		double Orion::MouseY()
		{
			return curr.Position.y;
		}

		double Orion::MouseWheelX()
		{
			return curr.Wheel.x;
		}

		double Orion::MouseWheelY()
		{
			return curr.Wheel.y;
		}

		double Orion::MouseWheelDx()
		{
			return prev.Wheel.x - curr.Wheel.x;
		}

		double Orion::MouseWheelDy()
		{
			return prev.Wheel.y - curr.Wheel.y;
		}

		void Orion::UpdateMouse()
		{
			double X, Y;
			glfwGetCursorPos(window, &X, &Y);
			prev.Position = curr.Position;
			curr.Position.x = X;
			curr.Position.y = Y;
		}

		void Orion::Update()
		{
			Input::Update();

			if (KeyboardPress(GLFW_KEY_W, GLFW_PRESS))						
				view->Forward(Osiris::PlayerVelocity);

			if (KeyboardPress(GLFW_KEY_S, GLFW_PRESS))
				view->Backward(Osiris::PlayerVelocity);

			if (KeyboardPress(GLFW_KEY_A, GLFW_PRESS))
				view->Left(Osiris::PlayerVelocity);

			if (KeyboardPress(GLFW_KEY_D, GLFW_PRESS))
				view->Right(Osiris::PlayerVelocity);

			if (KeyboardPress(GLFW_KEY_SPACE, GLFW_PRESS))
				view->Up(Osiris::PlayerVelocity);

			if (KeyboardPress(GLFW_KEY_LEFT_SHIFT, GLFW_PRESS))
				view->Down(Osiris::PlayerVelocity);			
			
			if (KeyboardPress(GLFW_KEY_E, GLFW_PRESS))
				view->ClockWise(Osiris::PlayerAngularVelocity);

			if (KeyboardPress(GLFW_KEY_Q, GLFW_PRESS))
				view->AntiClockWise(Osiris::PlayerAngularVelocity);

			if (KeyboardPress(GLFW_KEY_G, GLFW_CLICK))
				Osiris::WorldGravityEnable = !Osiris::WorldGravityEnable;

			if (KeyboardPress(GLFW_KEY_B, GLFW_CLICK))
				Osiris::PostEffectBloomEnable = !Osiris::PostEffectBloomEnable;

			if (KeyboardPress(GLFW_KEY_F, GLFW_CLICK))
				Osiris::PostEffectFieldBlurEnable = !Osiris::PostEffectFieldBlurEnable;

			if (KeyboardPress(GLFW_KEY_F2, GLFW_CLICK))
				Osiris::BiomeGlobalType = static_cast<BiomeType>(((int)Osiris::BiomeGlobalType + 1) % Osiris::BiomeCount);

			if (KeyboardPress(GLFW_KEY_F3, GLFW_CLICK))
				Osiris::DrawType = (Osiris::DrawType == GL_TRIANGLES) ? GL_LINES : GL_TRIANGLES;

			if (KeyboardPress(GLFW_KEY_F4, GLFW_CLICK))
				Osiris::DrawTerrainIndexBuffer = (Osiris::DrawTerrainIndexBuffer + 1) % Osiris::TerrainIndexBufferCount;

			if (KeyboardPress(GLFW_KEY_ESCAPE, GLFW_PRESS))
				glfwSetWindowShouldClose(window, true);			

			UpdateMouse();
			Calculate();	
		}

		bool MapPress(int (*f)(GLFWwindow*, int), GLFWwindow* window, map<int, int>& m, int i, int j)
		{
			if (j != GLFW_CLICK)
				return f(window, i) == j;

			int key = f(window, i);
			bool inMap = m.find(i) != m.end();

			if (key == GLFW_PRESS && !inMap)
				m[i] = GLFW_PRESS;

			if (key == GLFW_RELEASE && inMap)
			{
				if (m[i] == GLFW_PRESS)
				{
					m.erase(m.find(i));
					return true;
				}
			}
			return false;
		}

		bool Orion::KeyboardPress(int i, int j)
		{
			return MapPress(glfwGetKey, window, keyboardClickMap, i, j);
		}

		bool Orion::ButtonPress(int i, int j)
		{
			return MapPress(glfwGetMouseButton, window, buttonClickMap, i, j);
		}
	}
}