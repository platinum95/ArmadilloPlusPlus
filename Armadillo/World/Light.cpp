#include "Light.h"
#include <cmath>

namespace Armadillo
{
	namespace World
	{
		int LightDataSize = 12;

		float* Light::Data()
		{
			return this->fDataStream.data();
		}

		PointLight::PointLight(Armadillo::Maths::Vector3 position, Armadillo::Maths::Vector3 colour, Armadillo::Maths::Vector3 atten)
		{
			this->Position = position;
			this->Colour = colour;
			this->Attenuation = atten;
			this->Id = 0;
			this->fDataStream = std::vector<float>(LightDataSize, 0);
		}

		PointLight::~PointLight()
		{

		}

		void PointLight::Update()
		{
			int i = 0;
			this->fDataStream[i++] = Position.x;
			this->fDataStream[i++] = Position.y;
			this->fDataStream[i++] = Position.z;
			this->fDataStream[i++] = Id;
			this->fDataStream[i++] = Colour.x;
			this->fDataStream[i++] = Colour.y;
			this->fDataStream[i++] = Colour.z;
			i++;
			this->fDataStream[i++] = Attenuation.x;
			this->fDataStream[i++] = Attenuation.y;
			this->fDataStream[i++] = Attenuation.z;
		}		

		SpotLight::SpotLight(Armadillo::Maths::Vector3 position, Armadillo::Maths::Vector3 colour, Armadillo::Maths::Vector3 dir, float cut, float ocut)
		{
			this->Position = position;
			this->Colour = colour;
			this->Direction = dir;
			this->InnerCutOff = cut;
			this->OuterCutOff = ocut;
			this->Id = 1;
			this->fDataStream = std::vector<float>(LightDataSize, 0);
		}

		SpotLight::~SpotLight()
		{

		}

		void SpotLight::Update()
		{
			int i = 0;
			this->fDataStream[i++] = Position.x;
			this->fDataStream[i++] = Position.y;
			this->fDataStream[i++] = Position.z;
			this->fDataStream[i++] = Id;
			this->fDataStream[i++] = Colour.x;
			this->fDataStream[i++] = Colour.y;
			this->fDataStream[i++] = Colour.z;
			this->fDataStream[i++] = InnerCutOff;
			this->fDataStream[i++] = Direction.x;
			this->fDataStream[i++] = Direction.y;
			this->fDataStream[i++] = Direction.z;
			this->fDataStream[i++] = OuterCutOff;
		}

		ViewSpotLight::ViewSpotLight(Armadillo::Graphics::View* v, Armadillo::Maths::Vector3 colour, float cut, float ocut)
		{
			this->view = v;
			this->Colour = colour;			
			this->InnerCutOff = cut;
			this->OuterCutOff = ocut;
			this->Id = 2;
			this->fDataStream = std::vector<float>(LightDataSize, 0);
		}

		ViewSpotLight::~ViewSpotLight()
		{

		}

		void ViewSpotLight::Update()
		{
			int i = 0;
			this->fDataStream[i++] = view->Position.x;
			this->fDataStream[i++] = view->Position.y;
			this->fDataStream[i++] = view->Position.z;
			this->fDataStream[i++] = Id;
			this->fDataStream[i++] = Colour.x;
			this->fDataStream[i++] = Colour.y;
			this->fDataStream[i++] = Colour.z;
			this->fDataStream[i++] = InnerCutOff;
			this->fDataStream[i++] = -cos(view->Rotation.x) * cos(view->Rotation.y);
			this->fDataStream[i++] = sin(view->Rotation.x);
			this->fDataStream[i++] = -cos(view->Rotation.x) * sin(view->Rotation.y);
			this->fDataStream[i++] = OuterCutOff;
		}

		DirectionalLight::DirectionalLight(Armadillo::Maths::Vector3 dir, Armadillo::Maths::Vector3 colour)
		{
			this->Direction = dir;
			this->Colour = colour;
			this->Id = 2;
			this->fDataStream = std::vector<float>(LightDataSize, 0);
		}

		DirectionalLight::~DirectionalLight()
		{

		}

		void DirectionalLight::Update()
		{
			int i = 0;
			this->fDataStream[i++] = Direction.x;
			this->fDataStream[i++] = Direction.y;
			this->fDataStream[i++] = Direction.z;
			this->fDataStream[i++] = Id;
			this->fDataStream[i++] = Colour.x;
			this->fDataStream[i++] = Colour.y;
			this->fDataStream[i++] = Colour.z;
		}
	}
}