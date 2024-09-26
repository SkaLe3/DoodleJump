#pragma once

#include "Framework.h"

#include "Events.h"
#include "TriggerEvent.h"
#include "Math/MyMath.h"

#include <queue>
#include <unordered_map>

enum class EInputType : uint8_t
{
	Key, MouseButton, MouseMove
};


class InputEvent
{
public:
	InputEvent(EInputType it, ETriggerEvent is) : inputType(it), inputState(is) {}

	EInputType GetEventType() { return inputType; }

	ETriggerEvent GetInputState() { return inputState; }

protected:
	EInputType inputType;
	ETriggerEvent inputState;
};


class KeyEvent : public InputEvent
{
public:

	KeyEvent(FRKey _key, EInputType it, ETriggerEvent is) : InputEvent(it, is), key(_key) {}

	FRKey GetKey() const { return key; }

private:
	FRKey key;
};


class MouseButtonEvent : public InputEvent
{
public:
	MouseButtonEvent(FRMouseButton _button, EInputType it, ETriggerEvent is) : InputEvent(it, is), button(_button) {}
	FRMouseButton GetMouseButton() const { return button; }

private:
	FRMouseButton button;
};


class MouseMoveEvent : public InputEvent
{
public:
	MouseMoveEvent(Math::Vector2D _value, EInputType it, ETriggerEvent is) : InputEvent(it, is), m_Value(_value) {}
	Math::Vector2D GetValue() const { return m_Value; }

private:
	Math::Vector2D m_Value;
};


