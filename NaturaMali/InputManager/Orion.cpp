
#include "Orion.h"
#include "GLFW/glfw3.h"
#include "Osiris.h"
#include "Maths/VectorMath.h"
#include <cmath>
#include <iostream>
#include <thread>


namespace Armadillo
{
	namespace Management
	{
		Armadillo::World::Landscape* Orion::world = NULL;
		Armadillo::Graphics::View* Orion::view = NULL;
		Armadillo::Graphics::Projection* Orion::proj = NULL;
		Armadillo::Maths::Vector3* Orion::ePosition = NULL;
		Armadillo::Maths::Vector3* Orion::eRotation = NULL;
		Armadillo::World::Terrain* Orion::currTerrain = NULL;
		Armadillo::Physics::PhysicsEntity* Orion::viewEntity = NULL;
		GLFWwindow* Orion::window = NULL;

		float Orion::zoom = 50.0f;
		float Orion::angle = 0;

		Mouse Orion::curr;
		Mouse Orion::prev;

		std::map<int, int> Orion::ButtonClickMap = std::map<int, int>();
		std::map<int, int> Orion::KeyboardClickMap = std::map<int, int>();

		float ScrollSpeed = 30.0f;
		float Sensitivity = 0.0001f;

		Armadillo::World::RayCaster* Orion::Caster = NULL;

		void Orion::SetWorld(Armadillo::World::Landscape* w)
		{
			world = w;
		}


		void Orion::SetView(Armadillo::Graphics::View* v, Armadillo::Graphics::Projection* p)
		{
			view = v;
			proj = p;
			Caster = new Armadillo::World::RayCaster(view, proj);
		}

		void Orion::SetViewEntity(Armadillo::Physics::PhysicsEntity* _viewEntity) {
			Orion::viewEntity = _viewEntity;
		}

		void Orion::SetEntity(Armadillo::Maths::Vector3* p, Armadillo::Maths::Vector3* r)
		{
			ePosition = p;
			eRotation = r;
			Osiris::FreeViewEnable = false;
		}

		bool Orion::IsAllowedFreeView()
		{
			return true;// return ePosition != NULL && eRotation != NULL && Osiris::FreeViewEnable;
		}

		void Orion::GlutInit(GLFWwindow* w)
		{
			window = w;
			glfwSetKeyCallback(w, KeyboardEvent);
			glfwSetMouseButtonCallback(w, MouseEvent);
			glfwSetScrollCallback(w, MouseWheelEvent);
			glfwSetCursorPosCallback(w, MouseMoveEvent);
		}

		void Orion::CalculatePitch()
		{
			if (ButtonPress(GLFW_MOUSE_BUTTON_1, GLFW_PRESS))
			{
				view->Rotation.x -= Orion::MouseDy() * Osiris::PlayerCameraSensitivity;
			}
		}

		void Orion::CalculateYaw()
		{
			if (ButtonPress(GLFW_MOUSE_BUTTON_1, GLFW_PRESS))
			{
				if (!IsAllowedFreeView())
					view->Rotation.y = Pi - (eRotation->y + Orion::angle);
				else
					view->Rotation.y += Orion::MouseDx() * Osiris::PlayerCameraSensitivity;
			}
		}

		void Orion::CalculatePosition()
		{
			if (ButtonPress(GLFW_MOUSE_BUTTON_1, GLFW_PRESS))
			{
				float angleChange = Orion::MouseDx() * 0.01f;
				Orion::angle -= angleChange;
			}

			float vertical = Orion::zoom * sin(view->Rotation.x);
			float horizontal = Orion::zoom * cos(view->Rotation.x);

			float theta = eRotation->y + Orion::angle;

			view->Position.y = ePosition->y + vertical;
			view->Position.x = ePosition->x - horizontal * sin(theta);
			view->Position.z = ePosition->z - horizontal * cos(theta);
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
			if (!IsAllowedFreeView())
			{
				CalculateZoom();
				CalculatePosition();
			}
		}

		Armadillo::Maths::Vector3* Forward(Armadillo::Maths::Vector3* view)
		{
			Armadillo::Maths::Vector3* vec = new Armadillo::Maths::Vector3();
			vec->x = sin(view->y);
			vec->z = cos(view->y);
			return vec;
		}

		Armadillo::Maths::Vector3* Right(Armadillo::Maths::Vector3* view)
		{
			Armadillo::Maths::Vector3* forward = Forward(view);
			Armadillo::Maths::Vector4 vec4 = Armadillo::Maths::Matrix::RotationY(1.57079632679f) * Armadillo::Maths::Vector4(forward->x, forward->y, forward->z, 1.0f);

			return new Armadillo::Maths::Vector3(vec4);
		}


		double Orion::MouseDx()
		{
			float f = prev.mouse.x - curr.mouse.x;
			return abs(f) > Sensitivity ? f : 0;
		}

		double Orion::MouseDy()
		{
			float f = prev.mouse.y - curr.mouse.y;
			return abs(f) > Sensitivity ? f : 0;
		}

		double Orion::MouseX()
		{
			return curr.mouse.x;
		}

		double Orion::MouseY()
		{
			return curr.mouse.y;
		}

		double Orion::MouseWheelX()
		{
			return curr.wheel.x;
		}

		double Orion::MouseWheelY()
		{
			return curr.wheel.y;
		}

		double Orion::MouseWheelDx()
		{
			return prev.wheel.x - curr.wheel.x;
		}

		double Orion::MouseWheelDy()
		{
			return prev.wheel.y - curr.wheel.y;
		}

		Armadillo::Maths::Vector3* Orion::GetPosition()
		{
			return (!IsAllowedFreeView()) ? ePosition : &view->Position;
		}

		Armadillo::Maths::Vector3* Orion::GetRotation()
		{
			return &view->Rotation; //(entityEnabled) ? eRotation : &view->Rotation;
		}

		void Orion::Generate()
		{
			world->Generate();
		}


		void Orion::Gravity()
		{
			//	Gravity(view->Position, Osiris::PlayerHeight);
		}

		void Orion::Update()
		{
			Armadillo::Maths::Vector3* pos = GetPosition();
			Armadillo::Maths::Vector3* rot = GetRotation();
			if (KeyboardPress(GLFW_KEY_S, GLFW_PRESS))
			{
				Armadillo::Maths::Vector3 f = *Forward(rot);
				f = f * 20;
				viewEntity->addForce(f);
			}
			if (KeyboardPress(GLFW_KEY_W, GLFW_PRESS))
			{
				Armadillo::Maths::Vector3* g = Forward(rot);
				Armadillo::Maths::Vector3 f = Armadillo::Maths::Vector3(-g->x, -g->y, -g->z);

				f = f * 20;
				viewEntity->addForce(f);
			}
			if (KeyboardPress(GLFW_KEY_D, GLFW_PRESS))
			{
				Armadillo::Maths::Vector3* g = Right(rot);
				Armadillo::Maths::Vector3 f = Armadillo::Maths::Vector3(-g->x, -g->y, -g->z);
				f = f * 20;
				viewEntity->addForce(f);
			}
			if (KeyboardPress(GLFW_KEY_A, GLFW_PRESS))
			{
				Armadillo::Maths::Vector3 f = *Right(rot);
				f = f * 20;
				viewEntity->addForce(f);
			}
			if (KeyboardPress(GLFW_KEY_E, GLFW_PRESS))
				rot->y -= Osiris::PlayerAngularVelocity;

			if (KeyboardPress(GLFW_KEY_Q, GLFW_PRESS))
				rot->y += Osiris::PlayerAngularVelocity;

			if (KeyboardPress(GLFW_KEY_LEFT_SHIFT, GLFW_PRESS))
				pos->y -= Osiris::PlayerVelocity;

			if (KeyboardPress(GLFW_KEY_SPACE, GLFW_PRESS)) {
				Armadillo::Maths::Vector3* g = new Armadillo::Maths::Vector3(0, 400, 0);
				viewEntity->addForce(*g);
			}

			if (KeyboardPress(GLFW_KEY_E, GLFW_CLICK))
			{
				std::cout << pos->x << " " << pos->y << " " << pos->z << std::endl;
				std::cout << rot->x << " " << rot->y << " " << rot->z << std::endl;
			}

			if (KeyboardPress(GLFW_KEY_B, GLFW_CLICK))
				Osiris::FreeViewEnable = !Osiris::FreeViewEnable;

			if (KeyboardPress(GLFW_KEY_C, GLFW_CLICK))
				Osiris::FreeCameraEnable = !Osiris::FreeCameraEnable;

			if (KeyboardPress(GLFW_KEY_G, GLFW_CLICK))
				Osiris::WorldGravityEnable = !Osiris::WorldGravityEnable;

			if (KeyboardPress(GLFW_KEY_P, GLFW_PRESS))
			{
				view->Rotation.y = Pi - eRotation->y;
				Orion::angle = 0;
			}

			if (KeyboardPress(GLFW_KEY_F3, GLFW_CLICK))
				Osiris::DrawType = (Osiris::DrawType == GL_TRIANGLES) ? GL_LINES : GL_TRIANGLES;

			if (KeyboardPress(GLFW_KEY_F4, GLFW_CLICK))
				Osiris::DrawTerrainIndexBuffer = (Osiris::DrawTerrainIndexBuffer + 1) % Osiris::TerrainIndexBufferCount;

			if (KeyboardPress(GLFW_KEY_ESCAPE, GLFW_PRESS))
				glfwSetWindowShouldClose(window, true);

			Calculate();
			Caster->Update(curr.mouse.x, curr.mouse.y, currTerrain);
		}

		bool Orion::KeyboardPress(int i, int j)
		{
			if (j != GLFW_CLICK)
				return glfwGetKey(window, i) == j;

			int key = glfwGetKey(window, i);
			bool inMap = KeyboardClickMap.find(i) != KeyboardClickMap.end();

			if (key == GLFW_PRESS && !inMap)
				KeyboardClickMap[i] = GLFW_PRESS;

			if (key == GLFW_RELEASE && inMap)
			{
				if (KeyboardClickMap[i] == GLFW_PRESS)
				{
					KeyboardClickMap.erase(KeyboardClickMap.find(i));
					return true;
				}
			}
			return false;
		}

		bool Orion::ButtonPress(int i, int j)
		{
			if (j != GLFW_CLICK)
				return glfwGetMouseButton(window, i) == j;

			int key = glfwGetMouseButton(window, i);
			bool inMap = KeyboardClickMap.find(i) != KeyboardClickMap.end();

			if (key == GLFW_PRESS && !inMap)
				KeyboardClickMap[i] = GLFW_PRESS;

			if (key == GLFW_RELEASE && inMap)
			{
				if (KeyboardClickMap[i] == GLFW_PRESS)
				{
					KeyboardClickMap.erase(KeyboardClickMap.find(i));
					return true;
				}
			}
			return false;
		}

		void Orion::UpdateMouse(int x, int y)
		{
			prev.mouse.x = curr.mouse.x;
			prev.mouse.y = curr.mouse.y;
			curr.mouse.x = (float)x;
			curr.mouse.y = (float)y;
		}

		void Orion::KeyboardEvent(GLFWwindow* w, int key, int scan, int action, int mods)
		{

		}

		void Orion::MouseEvent(GLFWwindow* w, int button, int action, int mods)
		{

		}

		void Orion::MouseMoveEvent(GLFWwindow* w, double x, double y)
		{
			UpdateMouse(x, y);
		}

		void Orion::MouseWheelEvent(GLFWwindow* w, double xoffset, double yoffset)
		{
			prev.wheel.y = curr.wheel.y;
			prev.wheel.x = curr.wheel.x;
			curr.wheel.y = yoffset;
			curr.wheel.x = xoffset;
		}
	}
}
