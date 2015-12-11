#pragma once
#include "../Maths/VectorMath.h"

namespace Armadillo
{
	namespace Graphics
	{
		class View
		{
		public:
			Maths::Vector3 Position;
			Maths::Vector3 Rotation;

			View(Maths::Vector3, Maths::Vector3);
			~View();

			virtual Maths::Matrix GetMatrix();
			virtual Maths::Vector3 Forward();
			virtual Maths::Vector3 Left();
			virtual Maths::Vector3 Right();
			virtual Maths::Vector3 Backward();
			virtual Maths::Vector3 Up();
			virtual Maths::Vector3 Down();
			virtual void Forward(float);
			virtual void Left(float);
			virtual void Right(float);
			virtual void Backward(float);
			virtual void Up(float);
			virtual void Down(float);
			virtual void ClockWise(float);
			virtual void AntiClockWise(float);
		};		
	}
}
