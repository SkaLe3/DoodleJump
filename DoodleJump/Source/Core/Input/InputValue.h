#pragma once
#include "Math/MyMath.h"
#include <variant>

class InputValue
{
public:
	InputValue() : m_Value(double{1}) {}
	InputValue(double _value)	: m_Value(_value) {}
	InputValue(Math::Vector2D vec2d) : m_Value(vec2d) {}

	template<class T>
	T Get()
	{
		return std::get<T>(m_Value);
	}

private:
	std::variant<double, Math::Vector2D> m_Value;
};
