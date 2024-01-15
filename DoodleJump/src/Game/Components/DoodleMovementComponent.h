#pragma once

#include "Components/MovementComponent.h"

class DoodleMovementComponent : public MovementComponent
{
public:
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
};