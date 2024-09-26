#pragma once
#include "Components/MovementComponent.h"

class ProjectileMovementComponent : public MovementComponent
{
public:
	ProjectileMovementComponent();

	//~Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	//~End Object Interface

	void SetInitialVelocity(Math::Vector2D initialVelocity);
};