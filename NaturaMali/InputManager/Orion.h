#pragma once
#include "Graphics/View.h"
#include "Maths/VectorMath.h"
#include "World/Landscape.h"
#include "World/RayCaster.h"
#include "GLFW\glfw3.h"
#include <map>
#include <vector>
#include "Physics/PhysicsEntity.h"

#define GLFW_CLICK 500

namespace Armadillo
{
	namespace Management
	{
		struct Mouse
		{
			Armadillo::Maths::Vector2 wheel;
			Armadillo::Maths::Vector2 mouse;

		};

		class Orion
		{
		private:
			//Attributes
			static Armadillo::Maths::Vector3* ePosition;
			static Armadillo::Maths::Vector3* eRotation;
			static GLFWwindow* window;
			static float zoom;
			static float angle;

			static Mouse curr;
			static Mouse prev;

			static Armadillo::Graphics::View* view;
			static Armadillo::Graphics::Projection* proj;
			static Armadillo::World::Terrain* currTerrain;
			static Armadillo::World::Landscape* world;

			static std::map<int, int> ButtonClickMap;
			static std::map<int, int> KeyboardClickMap;

			//Methods
			static void UpdateMouse(int, int);
			static void Calculate();
			static void CalculateYaw();
			static void CalculatePitch();
			static void CalculatePosition();
			static void CalculateZoom();
			static int GetButtonIndex(int);
			static int GetSpecialIndex(int);
			static bool IsAllowedFreeView();

			static void Generate();

			static Armadillo::Maths::Vector3* GetPosition();
			static Armadillo::Maths::Vector3* GetRotation();

		public:
			//Attributes
			static Armadillo::World::RayCaster* Caster;
			static Armadillo::Physics::PhysicsEntity* viewEntity;

			//Methods
			static void SetView(Armadillo::Graphics::View*, Armadillo::Graphics::Projection*);
			static void SetEntity(Armadillo::Maths::Vector3*, Armadillo::Maths::Vector3*);
			static void SetWorld(Armadillo::World::Landscape*);
			static void SetViewEntity(Armadillo::Physics::PhysicsEntity*);

			static void Process();

			static void Gravity();
			static void Gravity(Armadillo::Maths::Vector3&, float);

			static void Update();

			static void KeyboardEvent(GLFWwindow*, int, int, int, int);
			static void MouseEvent(GLFWwindow*, int, int, int);
			static void MouseMoveEvent(GLFWwindow*, double, double);
			static void MouseWheelEvent(GLFWwindow*, double, double);

			static bool KeyboardPress(int, int);
			static bool ButtonPress(int, int);

			static double MouseDx();
			static double MouseDy();
			static double MouseX();
			static double MouseY();
			static double MouseWheelX();
			static double MouseWheelY();
			static double MouseWheelDx();
			static double MouseWheelDy();

			static void GlutInit(GLFWwindow*);
		};
	}
}