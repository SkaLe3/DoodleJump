#include "Vector2D.h"

#include "Vector.h"
#include "Vector4D.h"

namespace Math
{
	const Vector2D Vector2D::ZeroVector = { 0, 0 };

	Vector2D::Vector2D() : x(0), y(0) {}

	Vector2D::Vector2D(const Vector2D& v) : x(v.x), y(v.y) {}

	Vector2D::Vector2D(double scalar) : x(scalar), y(scalar) {}

	Vector2D::Vector2D(double a, double b) : x(a), y(b) {}

	Vector2D::Vector2D(const Vector& v) : x(v.x), y(v.y) {}

	Vector2D::Vector2D(const Vector4D& v) : x(v.x), y(v.y) {}

	double& Vector2D::operator[](size_t i)
	{
		switch (i)
		{
		default:
		case 0:
			return x;
		case 1:
			return y;
		}
	}

	const double& Vector2D::operator[](size_t i) const
	{
		switch (i)
		{
		default:
		case 0:
			return x;
		case 1:
			return y;
		}
	}

	Vector2D& Vector2D::operator=(const Vector2D& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	Vector2D& Vector2D::operator+=(const Vector2D& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Vector2D& Vector2D::operator+=(double scalar)
	{
		x += scalar;
		y += scalar;
		return *this;
	}

	Vector2D& Vector2D::operator-=(const Vector2D& v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}
	Vector2D& Vector2D::operator-=(double scalar)
	{
		x -= scalar;
		y -= scalar;
		return *this;
	}

	Vector2D& Vector2D::operator*=(const Vector2D& v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}

	Vector2D& Vector2D::operator*=(double scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector2D& Vector2D::operator/=(const Vector2D& v)
	{
		x /= v.x;
		y /= v.y;
		return *this;
	}

	Vector2D& Vector2D::operator/=(double scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

	// Unary operators
	Vector2D operator+(const Vector2D& v) { return v; }
	Vector2D operator-(const Vector2D& v) { return Vector2D(-v.x, -v.y); }

	// Binary operators
	Vector2D operator+(const Vector2D& v, double scalar) { return Vector2D(v.x + scalar, v.y + scalar); }
	Vector2D operator+(double scalar, const Vector2D& v) { return Vector2D(v.x + scalar, v.y + scalar); }
	Vector2D operator+(const Vector2D& v1, const Vector2D& v2) { return Vector2D(v1.x + v2.x, v1.y + v2.y); }

	Vector2D operator-(const Vector2D& v, double scalar) { return Vector2D(v.x - scalar, v.y - scalar); }
	Vector2D operator-(double scalar, const Vector2D& v) { return Vector2D(scalar - v.x, scalar - v.y); }
	Vector2D operator-(const Vector2D& v1, const Vector2D& v2) { return Vector2D(v1.x - v2.x, v1.y - v2.y); }

	Vector2D operator*(const Vector2D& v, double scalar) { return Vector2D(v.x * scalar, v.y * scalar); }
	Vector2D operator*(double scalar, const Vector2D& v) { return Vector2D(v.x * scalar, v.y * scalar); }
	Vector2D operator*(const Vector2D& v1, const Vector2D& v2) { return Vector2D(v1.x * v2.x, v1.y * v2.y); }

	Vector2D operator/(const Vector2D& v, double scalar) { return Vector2D(v.x / scalar, v.y / scalar); }
	Vector2D operator/(double scalar, const Vector2D& v) { return Vector2D(scalar / v.x, scalar / v.y); }
	Vector2D operator/(const Vector2D& v1, const Vector2D& v2) { return Vector2D(v1.x / v2.x, v1.y / v2.y); }

	// Boolean operators
	bool operator==(const Vector2D& v1, const Vector2D& v2) { return v1.x == v2.x && v1.y == v2.y; }
	bool operator!=(const Vector2D& v1, const Vector2D& v2) { return !(v1 == v2); }




}