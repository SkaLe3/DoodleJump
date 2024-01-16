#pragma once
#include "GameComponent.h"
#include "Math/Vector2D.h"

class MovementComponent : public GameComponent
{
public:
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;

public:
	void AddForce(Math::Vector2D force);
	Math::Vector2D GetVelocity() const { return velocity; }
protected:
	Math::Vector2D velocity;
	Math::Vector2D acceleration;
	double maxSpeed;

	
};