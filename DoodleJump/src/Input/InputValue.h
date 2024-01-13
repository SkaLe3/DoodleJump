#pragma once
#include "FMath.h"
#include <variant>

class InputValue
{
public:

	InputValue() : value(Math::Vector1D{ 1 }) {}
	InputValue(Math::Vector1D vec1d) : value(vec1d) {}
	InputValue(Math::Vector2D vec2d) : value(vec2d) {}

	template<class T>
	T Get()
	{
		return std::get<T>(value);
	}

private:
	std::variant<Math::Vector1D, Math::Vector2D> value;
};
