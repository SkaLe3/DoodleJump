#pragma once
#include <cstdint>

namespace Math
{
	struct Vector2D;
	struct Vector;
	struct Vector4D;

	double Dot(const Vector2D& v1, const Vector2D& v2);
	double Dot(const Vector& v1, const Vector& v2);
	double Dot(const Vector4D& v1, const Vector4D& v2);

	template<typename V>
	double Length(const V& v)
	{
		return sqrt(Dot(v, v));
	}

	template<typename V>
	double Distance(const V& v1, const V& v2)
	{
		return Length(v2 - v1);
	}

	Vector Cross(const Vector& v1, const Vector& v2);
	
	template<typename V>
	double Normalize(const V& v)
	{
		return v / Length(v);
	}

	double Clamp(double value, double minValue, double maxValue);
	int32_t Clamp(int32_t value, int32_t minValue, int32_t maxValue);
	Vector2D Clamp(const Vector2D& value, double minValue, double maxValue);
	Vector2D Clamp(const Vector2D& value, const Vector2D& minValue, const Vector2D& maxValue);

	Vector2D Abs(const Vector2D& v);


}