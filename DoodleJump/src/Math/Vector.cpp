#include "Vector.h"

#include "Vector2D.h"
#include "Vector4D.h"

namespace Math
{
	Vector::Vector() :x(0), y(0), z(0) {}

	Vector::Vector(const Vector& v) : x(v.x), y(v.y), z(v.z) {}

	Vector::Vector(double scalar) : x(scalar), y(scalar), z(scalar) {}

	Vector::Vector(double a, double b, double c) : x(a), y(b), z(c) {}

	Vector::Vector(const Vector2D& v, double _z) : x(v.x), y(v.y), z(_z) {}

	Vector::Vector(const Vector4D& v) : x(v.x), y(v.y), z(v.z) {}


	double& Vector::operator[](size_t i)
	{
		switch (i)
		{
		default:
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		}
	}

	const double& Vector::operator[](size_t i) const
	{
		switch (i)
		{
		default:
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
		}
	}
	Vector& Vector::operator=(const Vector& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return *this;
	}

	Vector& Vector::operator+=(const Vector& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	Vector& Vector::operator+=(double scalar)
	{
		x += scalar;
		y += scalar;
		z += scalar;
		return *this;
	}

	Vector& Vector::operator-=(const Vector& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	Vector& Vector::operator-=(double scalar)
	{
		x -= scalar;
		y -= scalar;
		z -= scalar;
		return *this;
	}

	Vector& Vector::operator*=(const Vector& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		return *this;
	}

	Vector& Vector::operator*=(double scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		return *this;
	}

	Vector& Vector::operator/=(const Vector& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		return *this;
	}

	Vector& Vector::operator/=(double scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		return *this;
	}
	
	// Unary operators
	Vector operator+(const Vector& v) { return v; }
	Vector operator-(const Vector& v) { return Vector(-v.x, -v.y, -v.z); }

	// Binary operators
	Vector operator+(const Vector& v, double scalar) { return Vector(v.x + scalar, v.y + scalar, v.z + scalar); }
	Vector operator+(double scalar, const Vector& v) { return Vector(v.x + scalar, v.y + scalar, v.z + scalar); }
	Vector operator+(const Vector& v1, const Vector& v2) { return Vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z); }

	Vector operator-(const Vector& v, double scalar) { return Vector(v.x - scalar, v.y - scalar, v.z - scalar); }
	Vector operator-(double scalar, const Vector& v) { return Vector(scalar - v.x, scalar - v.y, scalar - v.z); }
	Vector operator-(const Vector& v1, const Vector& v2) { return Vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z); }

	Vector operator*(const Vector& v, double scalar) { return Vector(v.x * scalar, v.y * scalar, v.z * scalar); }
	Vector operator*(double scalar, const Vector& v) { return Vector(v.x * scalar, v.y * scalar, v.z * scalar); }
	Vector operator*(const Vector& v1, const Vector& v2) { return Vector(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z); }

	Vector operator/(const Vector& v, double scalar) { return Vector(v.x / scalar, v.y / scalar, v.z / scalar); }
	Vector operator/(double scalar, const Vector& v) { return Vector(scalar / v.x, scalar / v.y, scalar / v.z); }
	Vector operator/(const Vector& v1, const Vector& v2) { return Vector(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z); }

	// Boolean operators
	bool operator==(const Vector& v1, const Vector& v2) { return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z; }
	bool operator!=(const Vector& v1, const Vector& v2) { return !(v1 == v2); }





}