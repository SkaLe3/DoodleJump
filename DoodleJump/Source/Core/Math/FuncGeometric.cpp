#include "FuncGeometric.h"

#include "Vector.h"
#include "Vector2D.h"
#include "Vector4D.h"
#include "Matrix4.h"


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

	double Clamp(double value, double minValue, double maxValue)
	{
		return std::min(maxValue, std::max(value, minValue));
	}

	int32_t Clamp(int32_t value, int32_t minValue, int32_t maxValue)
	{
		return std::min(maxValue, std::max(value, minValue));
	}

	Vector2D Clamp(const Vector2D& value, double minValue, double maxValue)
	{
		Vector2D temp = value;
		temp.x = std::min(maxValue, std::max(value.x, minValue));
		temp.y = std::min(maxValue, std::max(value.y, minValue));
		return temp;
	}

	Vector2D Clamp(const Vector2D& value, const Vector2D& minValue, const Vector2D& maxValue)
	{
		Vector2D temp = value;
		temp.x = Clamp(value.x, minValue.x, maxValue.x);
		temp.y = Clamp(value.y, minValue.y, maxValue.y);
		return temp;
	}

	Math::Vector2D Abs(const Vector2D& v)
	{
		Vector2D temp;
		temp.x = abs(v.x);
		temp.y = abs(v.y);
		return temp;
	}

}