#pragma once
#include "Framework.h"
#include "TriggerEvent.h"
#include "Math/MyMath.h"


enum class EInputType : uint8_t
{
	Key, MouseButton, MouseMove
};


class InputEvent
{
public:
	InputEvent(EInputType it, ETriggerEvent is) : m_InputType(it), m_InputState(is) {}

	EInputType GetEventType() { return m_InputType; }

	ETriggerEvent GetInputState() { return m_InputState; }

protected:
	EInputType m_InputType;
	ETriggerEvent m_InputState;
};


class KeyEvent : public InputEvent
{
public:

	KeyEvent(FRKey _key, EInputType it, ETriggerEvent is) : InputEvent(it, is), m_Key(_key) {}

	FRKey GetKey() const { return m_Key; }

private:
	FRKey m_Key;
};


class MouseButtonEvent : public InputEvent
{
public:
	MouseButtonEvent(FRMouseButton _button, EInputType it, ETriggerEvent is) : InputEvent(it, is), m_Button(_button) {}
	FRMouseButton GetMouseButton() const { return m_Button; }

private:
	FRMouseButton m_Button;
};


class MouseMoveEvent : public InputEvent
{
public:
	MouseMoveEvent(Math::Vector2D _value, EInputType it, ETriggerEvent is) : InputEvent(it, is), m_Value(_value) {}
	Math::Vector2D GetValue() const { return m_Value; }

private:
	Math::Vector2D m_Value;
};


