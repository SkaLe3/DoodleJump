#pragma once

namespace Math
{
	struct Vector;
	struct Vector4D;

	struct Vector2D
	{
		double x;
		double y;

		static const Vector2D ZeroVector;

		double& operator[](size_t i);
		const double& operator[](size_t i) const;

		// Basic constructors
		Vector2D();
		Vector2D(const Vector2D& v);
		Vector2D(double scalar);
		Vector2D(double a, double b);
		
		// Conversion constructors
		Vector2D(const Vector& v);
		Vector2D(const Vector4D& v);

		// Unary operators
		Vector2D& operator=(const Vector2D& v);
		Vector2D& operator+=(double scalar);
		Vector2D& operator+=(const Vector2D& v);
		Vector2D& operator-=(const Vector2D& v);
		Vector2D& operator-=(double scalar);
		Vector2D& operator*=(const Vector2D& v);
		Vector2D& operator*=(double scalar);
		Vector2D& operator/=(const Vector2D& v);
		Vector2D& operator/=(double scalar);

	};
	// Unary operators
	Vector2D operator+(const Vector2D& v);
	Vector2D operator-(const Vector2D& v);

	// Binary operators
	Vector2D operator+(const Vector2D& v, double scalar);
	Vector2D operator+(double scalar, const Vector2D& v);
	Vector2D operator+(const Vector2D& v1, const Vector2D& v2);

	Vector2D operator-(const Vector2D& v, double scalar);
	Vector2D operator-(double scalar, const Vector2D& v);
	Vector2D operator-(const Vector2D& v1, const Vector2D& v2);

	Vector2D operator*(const Vector2D& v, double scalar);
	Vector2D operator*(double scalar, const Vector2D& v);
	Vector2D operator*(const Vector2D& v1, const Vector2D& v2);

	Vector2D operator/(const Vector2D& v, double scalar);
	Vector2D operator/(double scalar, const Vector2D& v);
	Vector2D operator/(const Vector2D& v1, const Vector2D& v2);

	// Boolean operators
	bool operator==(const Vector2D& v1, const Vector2D& v2);
	bool operator!=(const Vector2D& v1, const Vector2D& v2);
}