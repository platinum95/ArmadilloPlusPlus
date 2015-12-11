#include "RayCaster.h"
#include "../Osiris.h"
#include "../Graphics/View.h"
#include "../Graphics/Projection.h"
#include "Terrain.h"


namespace Armadillo
{
	namespace World
	{
		using namespace Maths;
		using namespace Graphics;

		const float RayRange = 600;
		const float RecurseCount = 200;

		RayCaster::RayCaster(View* view, Projection* projection)
		{
			this->view = view;
			this->projection = projection;
			this->Ray = new Vector3(0, 0, 0);
			this->WorldPoint = new Vector3(0, 0, 0);
			this->terrain = NULL;
			this->PointOnRay = new Vector3(0, 0, 0);
		}

		RayCaster::~RayCaster()
		{
			delete this->Ray;
			delete this->WorldPoint;
		}

		void SetPointerToValue(Vector3* v, Vector3& v2)
		{
			v->x = v2.x;
			v->y = v2.y;
			v->z = v2.z;
		}

		Vector4 RayCaster::ToEyeCoords(Vector4 clipCoords)
		{			
			Vector4 coords = Matrix::Inverse(this->projection->GetMatrix()) * (clipCoords);
			return Vector4(coords.x, coords.y, -1, 0);
		}

		Vector3 RayCaster::ToWorldCoords(Vector4 eyeCoords)
		{
			Vector4 coords = Matrix::Inverse(this->view->GetMatrix()) * (eyeCoords);
			return Vector3(coords.x, coords.y, coords.z);			
		}

		Vector3* RayCaster::GetRay(int i, int j)
		{
			float x = (2.0f * i) / Osiris::DisplayWidth - 1;
			float y = (2.0f * -j) / Osiris::DisplayHeight + 1;

			Vector4 clipCoords = Vector4(x, y, -1, 1);
			Vector4 eyeCoords = ToEyeCoords(clipCoords);
			SetPointerToValue(this->Ray, ToWorldCoords(eyeCoords));
			return this->Ray;
		}

		void RayCaster::Update(int x, int y, Armadillo::World::Terrain* terrain)
		{
			this->GetRay(x, y);
			this->GetWorldPoint(terrain);
		}

		Vector3* RayCaster::GetWorldPoint(Armadillo::World::Terrain* terrain)
		{
			this->terrain = terrain;
			if (IntersectionInRange(0, RayRange, this->Ray))
				this->WorldPoint = BinarySearch(0, 0, RayRange, this->Ray);
			else
				this->WorldPoint = NULL;
			return this->WorldPoint;
		}

		Vector3 RayCaster::GetPointOnRay(Vector3* ray, float distance)
		{
			Vector3 result = Vector3(
				view->Position.x + ray->x * distance,
				view->Position.y + ray->y * distance,
				view->Position.z + ray->z * distance);
			return result;
		}

		Vector3* RayCaster::BinarySearch(int count, float start, float end, Vector3* ray)
		{
			float half = start + ((end - start) / 2.0f);
			if (count >= RecurseCount)
			{			
				SetPointerToValue(this->PointOnRay, GetPointOnRay(ray, half));
				return (this->terrain != NULL) ? PointOnRay : NULL;
			}
			if (IntersectionInRange(start, half, ray))
				return BinarySearch(count + 1, start, half, ray);
			else
				return BinarySearch(count + 1, half, end, ray);
		}

		bool RayCaster::IntersectionInRange(float start, float end, Vector3* ray)
		{
			Vector3 startPoint = GetPointOnRay(ray, start);
			Vector3 endPoint = GetPointOnRay(ray, end);
			return (!IsUnderTerrain(startPoint) && IsUnderTerrain(endPoint));
		}

		bool RayCaster::IsUnderTerrain(Vector3 point)
		{
			float height = 0;
			if (this->terrain != NULL)
				height = terrain->GetHeight(point.x, point.z);

			if (point.y < height)
				return true;
			return false;
		}

		View* RayCaster::GetView()
		{
			return this->view;
		}
	}
}