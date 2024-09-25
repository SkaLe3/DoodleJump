#pragma once


namespace Math
{
	struct Vector2D;
	struct Vector;

	struct Vector4D
	{
		double x;
		double y;
		double z;
		double w;

		double& operator[](size_t i);
		const double& operator[](size_t i) const;

		// Basic constructors
		Vector4D();
		Vector4D(const Vector4D& v);
		Vector4D(double scalar);
		Vector4D(double a, double b, double c, double d);

		// Conversion constructors
		Vector4D(const Vector2D& v, double _z, double _w);
		Vector4D(const Vector& v, double _w);

		// Unary operators
		Vector4D& operator=(const Vector4D& v);
		Vector4D& operator+=(double scalar);
		Vector4D& operator+=(const Vector4D& v);
		Vector4D& operator-=(const Vector4D& v);
		Vector4D& operator-=(double scalar);
		Vector4D& operator*=(const Vector4D& v);
		Vector4D& operator*=(double scalar);
		Vector4D& operator/=(const Vector4D& v);
		Vector4D& operator/=(double scalar);

	};
	// Unary operators
	Vector4D operator+(const Vector4D& v);
	Vector4D operator-(const Vector4D& v);

	// Binary operators
	Vector4D operator+(const Vector4D& v, double scalar);
	Vector4D operator+(double scalar, const Vector4D& v);
	Vector4D operator+(const Vector4D& v1, const Vector4D& v2);

	Vector4D operator-(const Vector4D& v, double scalar);
	Vector4D operator-(double scalar, const Vector4D& v);
	Vector4D operator-(const Vector4D& v1, const Vector4D& v2);

	Vector4D operator*(const Vector4D& v, double scalar);
	Vector4D operator*(double scalar, const Vector4D& v);
	Vector4D operator*(const Vector4D& v1, const Vector4D& v2);

	Vector4D operator/(const Vector4D& v, double scalar);
	Vector4D operator/(double scalar, const Vector4D& v);
	Vector4D operator/(const Vector4D& v1, const Vector4D& v2);

	// Boolean operators
	bool operator==(const Vector4D& v1, const Vector4D& v2);
	bool operator!=(const Vector4D& v1, const Vector4D& v2);
}
