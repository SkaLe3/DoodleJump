#pragma once

namespace Math
{
	struct Vector2D;
	struct Vector4D;

	struct Vector
	{
		double x;
		double y;
		double z;

		double& operator[](size_t i);
		const double& operator[](size_t i) const;

		// Basic constructors
		Vector();
		Vector(const Vector& v);
		Vector(double scalar);
		Vector(double a, double b, double c);

		// Conversion constructors
		Vector(const Vector2D& v, double _z);
		Vector(const Vector4D& v);

		// Unary operators
		Vector& operator=(const Vector& v);
		Vector& operator+=(double scalar);
		Vector& operator+=(const Vector& v);
		Vector& operator-=(const Vector& v);
		Vector& operator-=(double scalar);
		Vector& operator*=(const Vector& v);
		Vector& operator*=(double scalar);
		Vector& operator/=(const Vector& v);
		Vector& operator/=(double scalar);

	};
	// Unary operators
	Vector operator+(const Vector& v);
	Vector operator-(const Vector& v);

	// Binary operators
	Vector operator+(const Vector& v, double scalar);
	Vector operator+(double scalar, const Vector& v);
	Vector operator+(const Vector& v1, const Vector& v2);

	Vector operator-(const Vector& v, double scalar);
	Vector operator-(double scalar, const Vector& v);
	Vector operator-(const Vector& v1, const Vector& v2);

	Vector operator*(const Vector& v, double scalar);
	Vector operator*(double scalar, const Vector& v);
	Vector operator*(const Vector& v1, const Vector& v2);

	Vector operator/(const Vector& v, double scalar);
	Vector operator/(double scalar, const Vector& v);
	Vector operator/(const Vector& v1, const Vector& v2);

	// Boolean operators
	bool operator==(const Vector& v1, const Vector& v2);
	bool operator!=(const Vector& v1, const Vector& v2);
}