#pragma once
#include "Components/MovementComponent.h"

class ProjectileMovementComponent : public MovementComponent
{
public:
	ProjectileMovementComponent();

	virtual void Start() override;
	virtual void Tick(double deltaTime) override;

	void SetInitialVelocity(Math::Vector2D initialVelocity);
private:
};