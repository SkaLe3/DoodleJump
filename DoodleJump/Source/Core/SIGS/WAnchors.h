#pragma once
#include "Core/Math/Vector2D.h"


struct WAnchors
{
	Math::Vector2D Minimum;
	Math::Vector2D Maximum;
	
	WAnchors() : Minimum(0, 0), Maximum(0, 0) {}
	WAnchors(double horizontal, double vertical) : Minimum(horizontal, vertical), Maximum(horizontal, vertical) {}
	WAnchors(double minX, double minY, double maxX, double maxY) : Minimum(minX, minY), Maximum(maxX, maxY) {}
};