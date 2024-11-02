#pragma once
#include "Core/Math/Vector2D.h"

struct WMargin
{
	double Left;
	double Top;
	double Right;
	double Bottom;

	WMargin() : Left(0), Top(0), Right(0), Bottom(0) {}
	WMargin(double left, double top, double right, double bottom) : Left(left), Top(top), Right(right), Bottom(bottom) {}

	Math::Vector2D GetTopLeft() { return Math::Vector2D(Left, Top); }
	Math::Vector2D GetSize() { return Math::Vector2D(Left + Right, Top + Bottom); }
};