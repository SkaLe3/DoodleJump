#pragma once
#include "Components/BoxComponent.h"

namespace Physics
{
	bool IsColliding(const BoxCollider& object, const BoxCollider& other);
	BoxCollider GetBroadPhaseCollider(const BoxCollider& object);
	double SweptAABB(const BoxCollider& object, const BoxCollider& other, Math::Vector2D& normal);
}