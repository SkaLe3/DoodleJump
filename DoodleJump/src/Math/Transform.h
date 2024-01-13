#pragma once
#include "Vector.h"

namespace Math
{
	struct Transform
	{
		Math::Vector2D Translation = { 0.f, 0.f };
		Math::Vector2D Rotation = { 0.f, 0.f };
		Math::Vector2D Scale = { 0.f, 0.f };

		Transform() = default;
		Transform(const Transform&) = default;
		Transform(const Math::Vector2D translation) : Translation(translation) {}
	};

}