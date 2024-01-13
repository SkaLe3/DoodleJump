#pragma once
#include "Math/MyMath.h"
#include "Entities/Object.h"

class GameComponent : public Object
{
public:
	virtual ~GameComponent() {}
};

class SceneComponent : public GameComponent
{
public:
	GameComponent() = default;
	GameComponent(const Math::Vector2D& translation) : transform(translation) {}
	GameComponent(const Math::Transform& _transform) : transform(_transform) {}
protected:
	std::shared_ptr<Transform> transform;
};