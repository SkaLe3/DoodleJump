#pragma once
#include "Math/MyMath.h"
#include <variant>

class InputValue
{
public:

	InputValue() : value(double{1}) {}
	InputValue(double _value)	: value(_value) {}
	InputValue(Math::Vector2D vec2d) : value(vec2d) {}

	template<class T>
	T Get()
	{
		return std::get<T>(value);
	}

private:
	std::variant<double, Math::Vector2D> value;
};
