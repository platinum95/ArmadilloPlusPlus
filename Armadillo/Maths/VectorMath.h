#pragma once
#define Pi 3.14159265359

namespace Armadillo
{
	namespace Maths
	{
		struct Vector2;
		struct Vector2i;
		struct Vector3;
		struct Vector4;
		struct Matrix;

		struct Vector2
		{
			float x;
			float y;

			Vector2();
			Vector2(float, float);
			Vector2(Vector2i);

			friend bool operator==(const Vector2&, const Vector2&);
			friend Vector2 operator+ (const Vector2&, const Vector2&);
			friend Vector2 operator- (const Vector2&, const Vector2&);
			friend Vector2 operator* (const Vector2&, float);
			Vector2& operator= (const Vector2&);
			Vector2& operator=(const Vector2i&);
		};
		
		struct Vector2i
		{
			int x, y;

			Vector2i();
			Vector2i(int, int);
			Vector2i(Vector2);

			friend bool operator==(const Vector2i&, const Vector2i&);
			
			Vector2i& operator=(const Vector2i&);
			Vector2i& operator=(const Vector2&);
		};

		struct Vector3
		{
			float x;
			float y;
			float z;

			Vector3();
			Vector3(float, float, float);
			Vector3(const Vector2&, float);
			Vector3(const Vector4&);
			friend Vector3 operator+ (const Vector3&, const Vector3&);
			friend Vector3 operator+ (const Vector3&, float);
			friend Vector3& operator+= (Vector3&, const Vector3&);
			friend Vector3 operator- (const Vector3&, const Vector3&);
			friend Vector3 operator- (const Vector3&, float);
			friend Vector3& operator-= (Vector3&, const Vector3&);
			friend Vector3 operator* (const Vector3&, float);
			friend Vector3& operator*=(Vector3&, float);
			friend Vector3 operator/ (const Vector3&, float);
			Vector3& operator= (const Vector3&);

			static Vector3 Negate(const Vector3&);
			static float Length(const Vector3&);
			static float LengthSquared(const Vector3&);
			static Vector3 squareKeepSign(const Vector3&);
			static Vector3 Normalisation(const Vector3&);
			static float Dot(const Vector3&, const Vector3&);
			static Vector3 Cross(const Vector3&, const Vector3&);
		};

		struct Vector4
		{
			float x;
			float y;
			float z;
			float w;

			Vector4();
			Vector4(float, float, float, float);
			Vector4(const Vector2&, float, float);
			Vector4(const Vector3&, float);
			Vector4(const Vector2&, const Vector2&);

			Vector4& operator= (const Vector4&);
		};

		struct Matrix
		{
			float m[16];

			Matrix();
			Matrix(float, float, float, float,
				float, float, float, float,
				float, float, float, float,
				float, float, float, float);
			Vector4 operator* (const Vector4&);
			Matrix operator* (const Matrix&);
			Matrix& operator= (const Matrix&);
			Matrix operator+ (const Matrix&);
			Matrix operator- (const Matrix&);
			Matrix operator* (float);
			Matrix& operator+= (const Matrix&);
			Matrix& operator-= (const Matrix&);

			//Statics
			static Matrix Zero();
			static Matrix Identity();
			static float Determinant(const Matrix&);
			static Matrix Inverse(const Matrix&);
			static Matrix Tranpose(const Matrix&);
			static Matrix Translation(const Vector3&);
			static Matrix RotationX(float);
			static Matrix RotationY(float);
			static Matrix RotationZ(float);
			static Matrix Rotation(const Vector3&);
			static Matrix Scale(const Vector3&);
			static Matrix Scale(float);
			static Matrix ModelMatrix(const Vector3&, const Vector3&, float);
			static Matrix LookAt(const Vector3&, const Vector3&, const Vector3&);
			static Matrix Perspective(float, float, float, float);
			static Matrix Perspective(float, float, float, float, float, float);
			static Matrix Orthographic(float, float, float, float, float, float);
			static Matrix Diagonal(float, float, float, float);
		};
	}
}