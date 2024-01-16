#pragma once

#include "Components/MovementComponent.h"
#include "Math/Vector2D.h"

class DoodleMovementComponent : public MovementComponent
{
public:
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;

	void AddMovementInput(Math::Vector2D direction);
private:
	double gravity;
};