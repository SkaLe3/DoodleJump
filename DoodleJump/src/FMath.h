#pragma once
#include <cstdint>
namespace Math
{
	struct Vector1D
	{
		Vector1D(int32_t x) : X(x) {}
		int32_t X;
	};

	struct Vector2D
	{
		Vector2D(int32_t x, int32_t y) : X(x), Y(y) {}
		Vector2D(const Vector2D& other) : X(other.X), Y(other.Y) {}

		int32_t X;
		int32_t Y;
	};
}