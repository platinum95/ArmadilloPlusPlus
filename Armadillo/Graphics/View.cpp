#include "View.h"
#include <cmath>

namespace Armadillo
{
	namespace Graphics
	{
		using namespace Maths;		

		View::View(Vector3 pos, Vector3 rot)
		{
			this->Position = pos;
			this->Rotation = rot;
		}

		View::~View()
		{

		}

		Matrix View::GetMatrix()
		{
			return Matrix::Rotation(this->Rotation) * Matrix::Translation(Vector3::Negate(this->Position));
		}

		Vector3 View::Forward()		
		{
			return Vector3(-sin(this->Rotation.y), 0, -cos(this->Rotation.y));
		}

		Vector3 View::Left()
		{
			return Vector3(-cos(this->Rotation.y), 0, sin(this->Rotation.y));
		}

		Vector3 View::Right()
		{
			return Vector3(cos(this->Rotation.y), 0, -sin(this->Rotation.y));
		}

		Vector3 View::Backward()
		{
			return Vector3(sin(this->Rotation.y), 0, cos(this->Rotation.y));
		}

		Vector3 View::Up()
		{
			return Vector3(0, 1, 0);
		}

		Vector3 View::Down()
		{
			return Vector3(0, -1, 0);
		}

		void View::Forward(float f)
		{
			this->Position += this->Forward() * f;
		}

		void View::Left(float f)
		{
			this->Position += this->Left() * f;
		}

		void View::Right(float f)
		{
			this->Position += this->Right() * f;
		}

		void View::Backward(float f)
		{
			this->Position += this->Backward() * f;
		}

		void View::Up(float f)
		{
			this->Position += this->Up() * f;
		}

		void View::Down(float f)
		{
			this->Position += this->Down() * f;
		}

		void View::ClockWise(float f)
		{
			this->Rotation.y += f;
		}

		void View::AntiClockWise(float f)
		{
			this->Rotation.y -= f;
		}
	}
}

