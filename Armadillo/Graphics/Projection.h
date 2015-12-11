#pragma once
#include "../Maths/VectorMath.h"

namespace Armadillo
{
	namespace Graphics
	{
		enum ProjectionMode
		{
			Perspective,
			Orthographic
		};

		class Projection
		{
		private:
			float fov;
			float aspectRatio;
			float nearPlane;
			float farPlane;
			ProjectionMode mode;

			Maths::Matrix matrix;

		public:
			Projection(ProjectionMode, float, float, float, float);
			~Projection();

			Maths::Matrix GetMatrix();
			void ChangeMode(ProjectionMode);
			void ChangeAspectRatio(float);
		};
	}
}



