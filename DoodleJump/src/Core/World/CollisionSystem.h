#pragma once
#include "Components/BoxComponent.h"

namespace Physics
{
	bool IsColliding(std::shared_ptr<BoxComponent>& object, std::shared_ptr<BoxComponent> other);
	double SweptAABB(std::shared_ptr<BoxComponent>& object, std::shared_ptr<BoxComponent> other, Math::Vector2D& normal);
}