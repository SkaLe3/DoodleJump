#include "DoodleMovementComponent.h"

// Testings
#include <iostream>

void DoodleMovementComponent::Start()
{
	MovementComponent::Start();
}

void DoodleMovementComponent::Tick(double deltaTime)
{
	MovementComponent::Tick(deltaTime);

}

void DoodleMovementComponent::AddMovementInput(Math::Vector2D direction)
{
	//AddForce(direction * );

}
