#include "Projection.h"

namespace Armadillo
{
	namespace Graphics
	{
		using namespace Maths;

		Projection::Projection(ProjectionMode m, float fov, float AspectRatio, float NearPlane, float FarPlane)
		{
			this->aspectRatio = AspectRatio;
			this->nearPlane = NearPlane;
			this->farPlane = FarPlane;
			this->fov = fov;
			this->mode = m;
			this->ChangeMode(m);
		}

		Projection::~Projection()
		{

		}

		void Projection::ChangeMode(ProjectionMode m)
		{
			switch (m)
			{
			case Armadillo::Graphics::Perspective:
				//this->matrix = Matrix::Perspective(this->fov, this->aspectRatio, this->nearPlane, this->farPlane);
				this->matrix = Matrix::Perspective(-this->aspectRatio, this->aspectRatio, 1, -1, this->nearPlane, this->farPlane);
				break;
			case Armadillo::Graphics::Orthographic:
				this->matrix = Matrix::Orthographic(-this->aspectRatio, this->aspectRatio, 1, -1, this->nearPlane, this->farPlane);
				break;
			}
		}

		void Projection::ChangeAspectRatio(float f)
		{
			this->aspectRatio = f;
			this->ChangeMode(this->mode);
		}

		Matrix Projection::GetMatrix()
		{
			return this->matrix;
		}

	}
}
