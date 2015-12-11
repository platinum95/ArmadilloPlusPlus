#pragma once
#include "Management\Input.h"
#include "GLFW/glfw3.h"

#include <map>
#include <vector>

#define GLFW_CLICK 500

namespace Armadillo
{
	namespace World
	{
		class Landscape;
	}

	namespace Graphics
	{
		class View;
		class Projection;
	}

	namespace Management
	{
		class Orion : public Input
		{
		private:
			//Attributes
			GLFWwindow* window;
			float zoom;
			float angle;

			//Methods
			void Calculate();
			void CalculateYaw();
			void CalculatePitch();			
			void CalculateZoom();
			void UpdateMouse();
		public:
			//Constructor
			Orion(GLFWwindow*, World::Landscape*, Graphics::View*, Graphics::Projection*);
			~Orion();

			void Update();

			bool KeyboardPress(int, int);
			bool ButtonPress(int, int);
			
			double MouseDx();
			double MouseDy();
			double MouseX();
			double MouseY();
			double MouseWheelX();
			double MouseWheelY();
			double MouseWheelDx();
			double MouseWheelDy();
		};
	}
}