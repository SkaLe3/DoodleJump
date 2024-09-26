#pragma once

#include "Components/MovementComponent.h"
#include "Math/Vector2D.h"

class DoodleMovementComponent : public MovementComponent
{
public:
	DoodleMovementComponent();

	//~Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	//~End Object Interface

	void AddMovementInput(Math::Vector2D direction);
	void Jump();
	void SetJumpVelocity(double jumpVelocity);

private:
	double m_JumpVelocity;
};