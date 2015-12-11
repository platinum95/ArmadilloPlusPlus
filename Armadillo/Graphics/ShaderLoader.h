#pragma once
#include "Shader.h"
#include <string>
#include "../Maths/VectorMath.h"
namespace Armadillo
{
	namespace Graphics
	{
		class ShaderLoader
		{
		public:
			static void LoadFloat(Shader*, std::string, float);
			static void LoadInteger(Shader*, std::string, int);
			static void LoadBoolean(Shader*, std::string, bool);
			static void LoadVector(Shader*, std::string, Armadillo::Maths::Vector2);
			static void LoadVector(Shader*, std::string, Armadillo::Maths::Vector3);
			static void LoadVector(Shader*, std::string, Armadillo::Maths::Vector4);
			static void LoadMatrix(Shader*, std::string, Armadillo::Maths::Matrix, bool = false);
			static void LoadVectorArray(Shader*, std::string, Armadillo::Maths::Vector4[], int);
		};
	}
}

