#include "FuncGeometric.h"

#include "Vector.h"
#include "Vector2D.h"
#include "Vector4D.h"

#include <cmath>
namespace Math
{

	double Dot(const Vector2D& v1, const Vector2D& v2)
	{
		Vector2D temp(v1 * v2);
		return temp.x + temp.y;
	}

	double Dot(const Vector& v1, const Vector& v2)
	{
		Vector temp(v1 * v2);
		return temp.x + temp.y + temp.z;
	}

	double Dot(const Vector4D& v1, const Vector4D& v2)
	{
		Vector4D temp(v1 * v2);
		return temp.x + temp.y + temp.z + temp.w;
	}

	Vector Cross(const Vector& v1, const Vector& v2)
	{
		return Vector(
			v1.y * v2.z - v2.y * v1.z,
			v2.x * v1.z - v1.x * v2.z,
			v1.x * v2.y - v2.x * v1.y);
	}


}