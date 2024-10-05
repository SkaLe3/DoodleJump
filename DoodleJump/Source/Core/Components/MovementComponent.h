#pragma once
#include "GameComponent.h"

class MovementComponent : public GameComponent
{
public:
	MovementComponent();

	//~Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;
	//~End Object Interface

	Math::Vector2D& GetVelocity() { return m_Velocity; }
	void SetVelocity(Math::Vector2D velocity) { m_Velocity = velocity;}

	void SetGravity(double gravityValue);
	void SetMaxSpeed(double speed);

	void OnCollision(double collisionTime);

protected:
	Math::Vector2D m_Velocity;
	Math::Vector2D m_Acceleration;
	Math::Vector2D m_Gravity;
	double m_MaxSpeed;
};