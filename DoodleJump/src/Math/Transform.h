#pragma once
#include "Vector.h"

namespace Math
{
	struct Transform
	{
		Math::Vector Translation = { 0.f, 0.f, 0.f };
		Math::Vector Rotation = { 0.f, 0.f, 0.f };
		Math::Vector Scale = { 0.f, 0.f, 0.f };

		Transform() = default;
		Transform(const Transform&) = default;
		Transform(const Math::Vector translation) : Translation(translation) {}
	};

}