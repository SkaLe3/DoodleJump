#pragma once
#include "GameComponent.h"
#include "Math/Vector2D.h"

class MovementComponent : public GameComponent
{
public:
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
protected:
	Math::Vector2D velocity;
	
};