#include "DoodleMovementComponent.h"

// Testings
#include <iostream>

DoodleMovementComponent::DoodleMovementComponent() : MovementComponent(), jumpVelocity(20)
{
}

void DoodleMovementComponent::Start()
{
	MovementComponent::Start();
}

void DoodleMovementComponent::Tick(double deltaTime)
{
	MovementComponent::Tick(deltaTime);

	velocity.x = 0;

}

void DoodleMovementComponent::AddMovementInput(Math::Vector2D direction)
{
	velocity.x = direction.x * maxSpeed;
}

void DoodleMovementComponent::Jump()
{
	velocity.y = jumpVelocity;
}

void DoodleMovementComponent::SetJumpVelocity(double velocity)
{
	jumpVelocity = velocity;
}
