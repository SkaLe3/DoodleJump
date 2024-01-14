#include "Vector4D.h"

#include "Vector2D.h"
#include "Vector.h"

namespace Math
{
	Vector4D::Vector4D() :x(0), y(0), z(0), w(0) {}

	Vector4D::Vector4D(const Vector4D& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}

	Vector4D::Vector4D(double scalar) : x(scalar), y(scalar), z(scalar), w(scalar) {}

	Vector4D::Vector4D(double a, double b, double c, double d) : x(a), y(b), z(c), w(d) {}

	Vector4D::Vector4D(const Vector2D& v, double _z, double _w) : x(v.x), y(v.y), z(_z), w(_w) {}

	Vector4D::Vector4D(const Vector& v, double _w) : x(v.x), y(v.y), z(v.z), w(_w) {}

	double& Vector4D::operator[](size_t i)
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
		case 3:
			return w;
		}
	}

	const double& Vector4D::operator[](size_t i) const
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
		case 3:
			return w;
		}
	}

	Vector4D& Vector4D::operator=(const Vector4D& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		return *this;
	}

	Vector4D& Vector4D::operator+=(const Vector4D& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	Vector4D& Vector4D::operator+=(double scalar)
	{
		x += scalar;
		y += scalar;
		z += scalar;
		w += scalar;
		return *this;
	}

	Vector4D& Vector4D::operator-=(const Vector4D& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}
	Vector4D& Vector4D::operator-=(double scalar)
	{
		x -= scalar;
		y -= scalar;
		z -= scalar;
		w -= scalar;
		return *this;
	}

	Vector4D& Vector4D::operator*=(const Vector4D& v)
	{
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;
		return *this;
	}

	Vector4D& Vector4D::operator*=(double scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}

	Vector4D& Vector4D::operator/=(const Vector4D& v)
	{
		x /= v.x;
		y /= v.y;
		z /= v.z;
		w /= v.w;
		return *this;
	}

	Vector4D& Vector4D::operator/=(double scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		w /= scalar;
		return *this;
	}

	// Unary operators
	Vector4D operator+(const Vector4D& v) { return v; }
	Vector4D operator-(const Vector4D& v) { return Vector4D(-v.x, -v.y, -v.z, -v.w); }

	// Binary operators
	Vector4D operator+(const Vector4D& v, double scalar) { return Vector4D(v.x + scalar, v.y + scalar, v.z + scalar, v.w + scalar); }
	Vector4D operator+(double scalar, const Vector4D& v) { return Vector4D(v.x + scalar, v.y + scalar, v.z + scalar, v.w + scalar); }
	Vector4D operator+(const Vector4D& v1, const Vector4D& v2) { return Vector4D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w); }

	Vector4D operator-(const Vector4D& v, double scalar) { return Vector4D(v.x - scalar, v.y - scalar, v.z - scalar, v.w - scalar); }
	Vector4D operator-(double scalar, const Vector4D& v) { return Vector4D(scalar - v.x, scalar - v.y, scalar - v.z, scalar - v.w); }
	Vector4D operator-(const Vector4D& v1, const Vector4D& v2) { return Vector4D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w); }

	Vector4D operator*(const Vector4D& v, double scalar) { return Vector4D(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar); }
	Vector4D operator*(double scalar, const Vector4D& v) { return Vector4D(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar); }
	Vector4D operator*(const Vector4D& v1, const Vector4D& v2) { return Vector4D(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w); }

	Vector4D operator/(const Vector4D& v, double scalar) { return Vector4D(v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar); }
	Vector4D operator/(double scalar, const Vector4D& v) { return Vector4D(scalar / v.x, scalar / v.y, scalar / v.z, scalar / v.w); }
	Vector4D operator/(const Vector4D& v1, const Vector4D& v2) { return Vector4D(v1.x / v2.x, v1.y / v1.y, v1.z / v2.z, v1.w / v2.w); }

	// Boolean operators
	bool operator==(const Vector4D& v1, const Vector4D& v2) { return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w; }
	bool operator!=(const Vector4D& v1, const Vector4D& v2) { return !(v1 == v2); }







	

}