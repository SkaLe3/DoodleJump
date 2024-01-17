#pragma once
#include "GameComponent.h"
#include "Math/Vector2D.h"

class MovementComponent : public GameComponent
{
public:
	MovementComponent();
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;

public:


	Math::Vector2D& GetVelocity() { return velocity; }

	void SetGravity(double gravityValue);
	void SetMaxSpeed(double speed);

	void OnCollision(double collisionTime);

protected:
	Math::Vector2D velocity;
	Math::Vector2D acceleration;
	Math::Vector2D gravity;
	double maxSpeed;

	
};