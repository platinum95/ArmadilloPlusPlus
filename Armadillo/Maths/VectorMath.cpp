#include "VectorMath.h"
#include <cmath>
#include <iostream>

namespace Armadillo
{
	namespace Maths
	{
		Vector2::Vector2() 
		{
			this->x = 0;
			this->y = 0;
		}

		Vector2::Vector2(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		Vector2::Vector2(Vector2i vi)
		{
			this->x = vi.x;
			this->y = vi.y;
		}

		Vector2& Vector2::operator=(const Vector2& v)
		{
			this->x = v.x;
			this->y = v.y;
			return *this;
		}

		Vector2& Vector2::operator=(const Vector2i& v)
		{
			this->x = (float)v.x;
			this->y = (float)v.y;
			return *this;
		}

		bool operator==(const Vector2& v, const Vector2& v2)
		{
			return v.x == v2.x && v.y == v2.y;
		}

		Vector2 operator+ (const Vector2& v, const Vector2& v2)
		{
			return Vector2(v.x + v2.x, v.y + v2.y);
		}

		Vector2 operator- (const Vector2& v, const Vector2& v2)
		{
			return Vector2(v.x - v2.x, v.y - v2.y);
		}

		Vector2 operator* (const Vector2& v, float f)
		{
			return Vector2(v.x * f, v.y * f);
		}

		Vector2i::Vector2i()
		{
			this->x = 0;
			this->y = 0;
		}

		Vector2i::Vector2i(int x, int y)
		{
			this->x = x;
			this->y = y;
		}

		Vector2i::Vector2i(Vector2 vi)
		{
			this->x = vi.x;
			this->y = vi.y;
		}

		bool operator==(const Vector2i& v, const Vector2i& v2)
		{
			return v.x == v2.x && v.y == v2.y;
		}

		Vector2i& Vector2i::operator=(const Vector2i& v)
		{
			this->x = v.x;
			this->y = v.y;
			return *this;
		}

		Vector2i& Vector2i::operator=(const Vector2& v)
		{
			this->x = (int)v.x;
			this->y = (int)v.y;
			return *this;
		}

		Vector3::Vector3()
		{
			this->x = 0;
			this->y = 0;
			this->z = 0;
		}

		Vector3::Vector3(float x, float y, float z)
		{
			this->x = x;
			this->y = y;
			this->z = z;
		}

		Vector3::Vector3(const Vector2& v, float z)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = z;
		}

		Vector3::Vector3(const Vector4& v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
		}

		Vector4::Vector4()
		{
			this->x = 0;
			this->y = 0;
			this->z = 0;
			this->w = 0;
		}

		Vector4::Vector4(float x, float y, float z, float w)
		{
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}

		Vector4::Vector4(const Vector2& v, float z, float w)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = z;
			this->w = w;
		}

		Vector4::Vector4(const Vector3& v, float w)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			this->w = w;
		}

		Vector4::Vector4(const Vector2& v, const Vector2& v2)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v2.x;
			this->w = v2.y;
		}

		Vector4& Vector4::operator=(const Vector4& v)
		{
			this->x = v.x;
			this->y = v.y;
			this->z = v.z;
			this->w = v.w;
			return *this;
		}

		Matrix::Matrix()
		{
			for (int i = 0; i < 16; i++)
				m[i] = 0;
		}

		Matrix::Matrix(float a, float b, float c, float d,
			float e, float f, float g, float h,
			float i, float j, float k, float l,
			float mm, float n, float o, float p) {
			m[0] = a;
			m[1] = e;
			m[2] = i;
			m[3] = mm;
			m[4] = b;
			m[5] = f;
			m[6] = j;
			m[7] = n;
			m[8] = c;
			m[9] = g;
			m[10] = k;
			m[11] = o;
			m[12] = d;
			m[13] = h;
			m[14] = l;
			m[15] = p;
		}

		float Vector3::LengthSquared(const Vector3& v)
		{
			return v.x * v.x + v.y * v.y + v.z * v.z;
		}

		float Vector3::Length(const Vector3& v)
		{
			return std::sqrt(Vector3::LengthSquared(v));
		}

		Vector3 Vector3::squareKeepSign(const Vector3& in) {
			Vector3 out;
			out.x = ((in.x < 0) ? -(in.x * in.x) : in.x * in.x);
			out.y = ((in.y < 0) ? -(in.y * in.y) : in.y * in.y);
			out.z = ((in.z < 0) ? -(in.z * in.z) : in.z * in.z);
			return out;
		}

		Vector3 Vector3::Normalisation(const Vector3& v)
		{
			Vector3 vb;
			float l = Vector3::Length(v);
			if (0.0f == l) {
				return Vector3(0.0f, 0.0f, 0.0f);
			}
			vb.x = v.x / l;
			vb.y = v.y / l;
			vb.z = v.z / l;
			return vb;
		}

		Vector3 Vector3::Negate(const Vector3& v)
		{
			return Vector3(-v.x, -v.y, -v.z);
		}

		Vector3 operator+ (const Vector3& lhs, const Vector3& rhs)
		{
			Vector3 vc;
			vc.x = lhs.x + rhs.x;
			vc.y = lhs.y + rhs.y;
			vc.z = lhs.z + rhs.z;
			return vc;
		}

		Vector3& operator+= (Vector3& lhs, const Vector3& rhs)
		{
			lhs.x += rhs.x;
			lhs.y += rhs.y;
			lhs.z += rhs.z;
			return lhs;
		}

		Vector3 operator- (const Vector3& lhs, const Vector3& rhs)
		{
			Vector3 vc;
			vc.x = lhs.x - rhs.x;
			vc.y = lhs.y - rhs.y;
			vc.z = lhs.z - rhs.z;
			return vc;
		}

		Vector3& operator-= (Vector3& lhs, const Vector3& rhs)
		{
			lhs.x -= rhs.x;
			lhs.y -= rhs.y;
			lhs.z -= rhs.z;
			return lhs;
		}

		Vector3 operator+ (const Vector3& lhs, float rhs)
		{
			Vector3 vc;
			vc.x = lhs.x + rhs;
			vc.y = lhs.y + rhs;
			vc.z = lhs.z + rhs;
			return vc;
		}

		Vector3 operator- (const Vector3& lhs, float rhs)
		{
			Vector3 vc;
			vc.x = lhs.x - rhs;
			vc.y = lhs.y - rhs;
			vc.z = lhs.z - rhs;
			return vc;
		}

		Vector3 operator* (const Vector3& lhs, float rhs)
		{
			Vector3 vc;
			vc.x = lhs.x * rhs;
			vc.y = lhs.y * rhs;
			vc.z = lhs.z * rhs;
			return vc;
		}

		Vector3 operator/ (const Vector3& lhs, float rhs)
		{
			Vector3 vc;
			vc.x = lhs.x / rhs;
			vc.y = lhs.y / rhs;
			vc.z = lhs.z / rhs;
			return vc;
		}

		Vector3& operator*= (Vector3& lhs, float rhs)
		{
			lhs.x = lhs.x * rhs;
			lhs.y = lhs.y * rhs;
			lhs.z = lhs.z * rhs;
			return lhs;
		}

		Vector3& Vector3::operator= (const Vector3& rhs)
		{
			x = rhs.x;
			y = rhs.y;
			z = rhs.z;
			return *this;
		}

		float Vector3::Dot(const Vector3& a, const Vector3& b) 
		{
			return a.x * b.x + a.y * b.y + a.z * b.z;
		}

		Vector3 Vector3::Cross(const Vector3& a, const Vector3& b)
		{
			float x = a.y * b.z - a.z * b.y;
			float y = a.z * b.x - a.x * b.z;
			float z = a.x * b.y - a.y * b.x;
			return Vector3(x, y, z);
		}

		Matrix Matrix::Zero()
		{
			return Matrix();
		}

		Matrix Matrix::Diagonal(float a, float b, float c, float d)
		{
			return Matrix(a, 0, 0, 0, 0, b, 0, 0, 0, 0, c, 0, 0, 0, 0, d);
		}

		Matrix Matrix::Identity()
		{
			return Matrix::Diagonal(1.0f, 1.0f, 1.0f, 1.0f);
		}

		Vector4 Matrix::operator* (const Vector4& rhs) 
		{
			float x = m[0] * rhs.x + m[4] * rhs.y + m[8] * rhs.z + m[12] * rhs.w;
			float y = m[1] * rhs.x + m[5] * rhs.y + m[9] * rhs.z + m[13] * rhs.w;
			float z = m[2] * rhs.x + m[6] * rhs.y + m[10] * rhs.z + m[14] * rhs.w;
			float w = m[3] * rhs.x + m[7] * rhs.y + m[11] * rhs.z + m[15] * rhs.w;
			return Vector4(x, y, z, w);
		}

		Matrix Matrix::operator* (const Matrix& rhs) 
		{
			Matrix r = Zero();
			int r_index = 0;
			for (int col = 0; col < 4; col++) 
			{
				for (int row = 0; row < 4; row++) 
				{
					float sum = 0.0f;
					for (int i = 0; i < 4; i++) 
					{
						sum += rhs.m[i + col * 4] * m[row + i * 4];
					}
					r.m[r_index] = sum;
					r_index++;
				}
			}
			return r;
		}

		Matrix& Matrix::operator= (const Matrix& rhs)
		{
			for (int i = 0; i < 16; i++)
			{
				m[i] = rhs.m[i];
			}
			return *this;
		}

		float Matrix::Determinant(const Matrix& mm)
		{
			return mm.m[12] * mm.m[9] * mm.m[6] * mm.m[3] -
				mm.m[8] * mm.m[13] * mm.m[6] * mm.m[3] -
				mm.m[12] * mm.m[5] * mm.m[10] * mm.m[3] +
				mm.m[4] * mm.m[13] * mm.m[10] * mm.m[3] +
				mm.m[8] * mm.m[5] * mm.m[14] * mm.m[3] -
				mm.m[4] * mm.m[9] * mm.m[14] * mm.m[3] -
				mm.m[12] * mm.m[9] * mm.m[2] * mm.m[7] +
				mm.m[8] * mm.m[13] * mm.m[2] * mm.m[7] +
				mm.m[12] * mm.m[1] * mm.m[10] * mm.m[7] -
				mm.m[0] * mm.m[13] * mm.m[10] * mm.m[7] -
				mm.m[8] * mm.m[1] * mm.m[14] * mm.m[7] +
				mm.m[0] * mm.m[9] * mm.m[14] * mm.m[7] +
				mm.m[12] * mm.m[5] * mm.m[2] * mm.m[11] -
				mm.m[4] * mm.m[13] * mm.m[2] * mm.m[11] -
				mm.m[12] * mm.m[1] * mm.m[6] * mm.m[11] +
				mm.m[0] * mm.m[13] * mm.m[6] * mm.m[11] +
				mm.m[4] * mm.m[1] * mm.m[14] * mm.m[11] -
				mm.m[0] * mm.m[5] * mm.m[14] * mm.m[11] -
				mm.m[8] * mm.m[5] * mm.m[2] * mm.m[15] +
				mm.m[4] * mm.m[9] * mm.m[2] * mm.m[15] +
				mm.m[8] * mm.m[1] * mm.m[6] * mm.m[15] -
				mm.m[0] * mm.m[9] * mm.m[6] * mm.m[15] -
				mm.m[4] * mm.m[1] * mm.m[10] * mm.m[15] +
				mm.m[0] * mm.m[5] * mm.m[10] * mm.m[15];
		}

		Matrix Matrix::Inverse(const Matrix& mm) 
		{
			float det = Determinant(mm);		
			if (0.0f == det) 							
				return mm;
			
			float inv_det = 1.0f / det;
			return Matrix(
				inv_det * (mm.m[9] * mm.m[14] * mm.m[7] - mm.m[13] * mm.m[10] * mm.m[7] + mm.m[13] * mm.m[6] * mm.m[11] - mm.m[5] * mm.m[14] * mm.m[11] - mm.m[9] * mm.m[6] * mm.m[15] + mm.m[5] * mm.m[10] * mm.m[15]),
				inv_det * (mm.m[12] * mm.m[10] * mm.m[7] - mm.m[8] * mm.m[14] * mm.m[7] - mm.m[12] * mm.m[6] * mm.m[11] + mm.m[4] * mm.m[14] * mm.m[11] + mm.m[8] * mm.m[6] * mm.m[15] - mm.m[4] * mm.m[10] * mm.m[15]),
				inv_det * (mm.m[8] * mm.m[13] * mm.m[7] - mm.m[12] * mm.m[9] * mm.m[7] + mm.m[12] * mm.m[5] * mm.m[11] - mm.m[4] * mm.m[13] * mm.m[11] - mm.m[8] * mm.m[5] * mm.m[15] + mm.m[4] * mm.m[9] * mm.m[15]),
				inv_det * (mm.m[12] * mm.m[9] * mm.m[6] - mm.m[8] * mm.m[13] * mm.m[6] - mm.m[12] * mm.m[5] * mm.m[10] + mm.m[4] * mm.m[13] * mm.m[10] + mm.m[8] * mm.m[5] * mm.m[14] - mm.m[4] * mm.m[9] * mm.m[14]),
				inv_det * (mm.m[13] * mm.m[10] * mm.m[3] - mm.m[9] * mm.m[14] * mm.m[3] - mm.m[13] * mm.m[2] * mm.m[11] + mm.m[1] * mm.m[14] * mm.m[11] + mm.m[9] * mm.m[2] * mm.m[15] - mm.m[1] * mm.m[10] * mm.m[15]),
				inv_det * (mm.m[8] * mm.m[14] * mm.m[3] - mm.m[12] * mm.m[10] * mm.m[3] + mm.m[12] * mm.m[2] * mm.m[11] - mm.m[0] * mm.m[14] * mm.m[11] - mm.m[8] * mm.m[2] * mm.m[15] + mm.m[0] * mm.m[10] * mm.m[15]),
				inv_det * (mm.m[12] * mm.m[9] * mm.m[3] - mm.m[8] * mm.m[13] * mm.m[3] - mm.m[12] * mm.m[1] * mm.m[11] + mm.m[0] * mm.m[13] * mm.m[11] + mm.m[8] * mm.m[1] * mm.m[15] - mm.m[0] * mm.m[9] * mm.m[15]),
				inv_det * (mm.m[8] * mm.m[13] * mm.m[2] - mm.m[12] * mm.m[9] * mm.m[2] + mm.m[12] * mm.m[1] * mm.m[10] - mm.m[0] * mm.m[13] * mm.m[10] - mm.m[8] * mm.m[1] * mm.m[14] + mm.m[0] * mm.m[9] * mm.m[14]),
				inv_det * (mm.m[5] * mm.m[14] * mm.m[3] - mm.m[13] * mm.m[6] * mm.m[3] + mm.m[13] * mm.m[2] * mm.m[7] - mm.m[1] * mm.m[14] * mm.m[7] - mm.m[5] * mm.m[2] * mm.m[15] + mm.m[1] * mm.m[6] * mm.m[15]),
				inv_det * (mm.m[12] * mm.m[6] * mm.m[3] - mm.m[4] * mm.m[14] * mm.m[3] - mm.m[12] * mm.m[2] * mm.m[7] + mm.m[0] * mm.m[14] * mm.m[7] + mm.m[4] * mm.m[2] * mm.m[15] - mm.m[0] * mm.m[6] * mm.m[15]),
				inv_det * (mm.m[4] * mm.m[13] * mm.m[3] - mm.m[12] * mm.m[5] * mm.m[3] + mm.m[12] * mm.m[1] * mm.m[7] - mm.m[0] * mm.m[13] * mm.m[7] - mm.m[4] * mm.m[1] * mm.m[15] + mm.m[0] * mm.m[5] * mm.m[15]),
				inv_det * (mm.m[12] * mm.m[5] * mm.m[2] - mm.m[4] * mm.m[13] * mm.m[2] - mm.m[12] * mm.m[1] * mm.m[6] + mm.m[0] * mm.m[13] * mm.m[6] + mm.m[4] * mm.m[1] * mm.m[14] - mm.m[0] * mm.m[5] * mm.m[14]),
				inv_det * (mm.m[9] * mm.m[6] * mm.m[3] - mm.m[5] * mm.m[10] * mm.m[3] - mm.m[9] * mm.m[2] * mm.m[7] + mm.m[1] * mm.m[10] * mm.m[7] + mm.m[5] * mm.m[2] * mm.m[11] - mm.m[1] * mm.m[6] * mm.m[11]),
				inv_det * (mm.m[4] * mm.m[10] * mm.m[3] - mm.m[8] * mm.m[6] * mm.m[3] + mm.m[8] * mm.m[2] * mm.m[7] - mm.m[0] * mm.m[10] * mm.m[7] - mm.m[4] * mm.m[2] * mm.m[11] + mm.m[0] * mm.m[6] * mm.m[11]),
				inv_det * (mm.m[8] * mm.m[5] * mm.m[3] - mm.m[4] * mm.m[9] * mm.m[3] - mm.m[8] * mm.m[1] * mm.m[7] + mm.m[0] * mm.m[9] * mm.m[7] + mm.m[4] * mm.m[1] * mm.m[11] - mm.m[0] * mm.m[5] * mm.m[11]),
				inv_det * (mm.m[4] * mm.m[9] * mm.m[2] - mm.m[8] * mm.m[5] * mm.m[2] + mm.m[8] * mm.m[1] * mm.m[6] - mm.m[0] * mm.m[9] * mm.m[6] - mm.m[4] * mm.m[1] * mm.m[10] + mm.m[0] * mm.m[5] * mm.m[10]));
		}

		Matrix Matrix::Tranpose(const Matrix& mm)
		{
			return Matrix(mm.m[0], mm.m[1], mm.m[2], mm.m[3],
				mm.m[4], mm.m[5], mm.m[6], mm.m[7],
				mm.m[8], mm.m[9], mm.m[10], mm.m[11],
				mm.m[12], mm.m[13], mm.m[14], mm.m[15]);
		}

		Matrix Matrix::Translation(const Vector3& v)
		{
			Matrix matrix = Matrix::Identity();
			matrix.m[12] = v.x;
			matrix.m[13] = v.y;
			matrix.m[14] = v.z;
			return matrix;
		}

		Matrix Matrix::RotationX(float rad)
		{
			Matrix matrix = Matrix::Identity();
			matrix.m[5] = std::cos(rad);
			matrix.m[9] = -std::sin(rad);
			matrix.m[6] = std::sin(rad);
			matrix.m[10] = std::cos(rad);
			return matrix;
		}

		Matrix Matrix::RotationY(float rad)
		{
			Matrix matrix = Matrix::Identity();
			matrix.m[0] = std::cos(rad);
			matrix.m[8] = -std::sin(rad);
			matrix.m[2] = std::sin(rad);
			matrix.m[10] = std::cos(rad);
			return matrix;
		}

		Matrix Matrix::RotationZ(float rad)
		{
			Matrix matrix = Matrix::Identity();
			matrix.m[0] = std::cos(rad);
			matrix.m[4] = -std::sin(rad);
			matrix.m[1] = std::sin(rad);
			matrix.m[5] = std::cos(rad);
			return matrix;
		}

		Matrix Matrix::Rotation(const Vector3& v)
		{
			return Matrix::RotationX(v.x) * Matrix::RotationY(v.y) * Matrix::RotationZ(v.z);
		}

		Matrix Matrix::Scale(const Vector3& v)
		{
			return Matrix::Diagonal(v.x, v.y, v.z, 1.0f);
		}

		Matrix Matrix::Scale(float f)
		{
			return Matrix::Diagonal(f, f, f, 1.0f);
		}

		Matrix Matrix::ModelMatrix(const Vector3& p, const Vector3& r, float s)
		{
			return Translation(p) * Rotation(r) * Scale(s);
		}

		Matrix Matrix::LookAt(const Vector3& camera, const Vector3& target, const Vector3& up)
		{
			Matrix p = Matrix::Translation(Vector3::Negate(camera));
			Vector3 f = Vector3::Normalisation(target - camera);
			Vector3 r = Vector3::Normalisation(Vector3::Cross(f, up));
			Vector3 u = Vector3::Normalisation(Vector3::Cross(r, f));
			Matrix ori = Matrix::Identity();
			ori.m[0] = r.x;
			ori.m[4] = r.y;
			ori.m[8] = r.z;
			ori.m[1] = u.x;
			ori.m[5] = u.y;
			ori.m[9] = u.z;
			ori.m[2] = -f.x;
			ori.m[6] = -f.y;
			ori.m[10] = -f.z;
			return ori;
		}

		Matrix Matrix::Perspective(float l, float r, float t , float b, float n, float f)
		{
			Matrix matrix;
			matrix.m[0] = 2 * n / (r - l);
			matrix.m[4] = 0;
			matrix.m[8] = (r + l) / (r - l);
			matrix.m[12] = 0;

			matrix.m[1] = 0;
			matrix.m[5] = 2 * n / (t - b);
			matrix.m[9] = (t + b) / (t - b);
			matrix.m[13] = 0;

			matrix.m[2] = 0;
			matrix.m[6] = 0;
			matrix.m[10] = -(f + n) / (f - n);
			matrix.m[14] = -2 * f / (f - n);

			matrix.m[3] = 0;
			matrix.m[7] = 0;
			matrix.m[11] = -1;
			matrix.m[15] = 0;
			return matrix;
		}

		Matrix Matrix::Perspective(float fov, float aspect, float n, float f) 
		{
			const float t = std::tan(fov*0.5f) * n;
			const float b = -t;

			const float l = aspect * b;
			const float r = aspect * t;

			return Matrix::Perspective(l, r, t, b, n, f);
		}

		Matrix Matrix::Orthographic(float l, float r, float b, float t, float n, float f)
		{
			float sx = 1 / (r - l);
			float sy = 1 / (t - b);
			float sz = 1 / (f - n);
			Matrix matrix;
			matrix.m[0] = 2 * sx;
			matrix.m[1] = 0;
			matrix.m[2] = 0;
			matrix.m[3] = -(r + l) * sx;
			matrix.m[4] = 0;
			matrix.m[5] = 2 * sy;
			matrix.m[6] = 0;
			matrix.m[7] = -(t + b) * sy;
			matrix.m[8] = 0;
			matrix.m[9] = 0;
			matrix.m[10] = -2 * sz;
			matrix.m[11] = -(n + f) * sz;
			matrix.m[12] = 0;
			matrix.m[13] = 0;
			matrix.m[14] = 0;
			matrix.m[15] = 1;
			return matrix;
		}
	}
}