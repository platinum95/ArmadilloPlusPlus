#pragma once
#include "../Maths/VectorMath.h"
#include "../Graphics/View.h"
#include <vector>

namespace Armadillo
{
	namespace World
	{
		extern int LightDataSize;

		class Light
		{
		protected:
			std::vector<float> fDataStream;
		public:
			int Id;
			Armadillo::Maths::Vector3 Colour;

			virtual void Update() = 0;			
			float* Data();
			
			virtual ~Light() { };
		};

		class PointLight : public Light
		{
		public:
			Armadillo::Maths::Vector3 Position;
			Armadillo::Maths::Vector3 Attenuation;

			PointLight(Armadillo::Maths::Vector3, Armadillo::Maths::Vector3, Armadillo::Maths::Vector3);
			~PointLight();

			void Update();
		};

		class SpotLight : public Light
		{
		public:
			Armadillo::Maths::Vector3 Position;
			Armadillo::Maths::Vector3 Direction;
			float InnerCutOff, OuterCutOff;

			SpotLight(Armadillo::Maths::Vector3, Armadillo::Maths::Vector3, Armadillo::Maths::Vector3, float, float);
			~SpotLight();

			void Update();
		};

		class ViewSpotLight : public Light
		{
		private:
			Armadillo::Graphics::View* view;
			float InnerCutOff, OuterCutOff;
		public:
			ViewSpotLight(Armadillo::Graphics::View*, Armadillo::Maths::Vector3, float, float);
			~ViewSpotLight();

			void Update();
		};

		class DirectionalLight : public Light
		{
		public:
			Armadillo::Maths::Vector3 Direction;

			DirectionalLight(Armadillo::Maths::Vector3, Armadillo::Maths::Vector3);
			~DirectionalLight();

			void Update();
		};
	}
}