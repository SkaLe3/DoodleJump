#include "ProjectileMovementComponent.h"

ProjectileMovementComponent::ProjectileMovementComponent() : MovementComponent()
{

}

void ProjectileMovementComponent::Start()
{
	MovementComponent::Start();
}

void ProjectileMovementComponent::Tick(double DeltaTime)
{
	MovementComponent::Tick(DeltaTime);
}

void ProjectileMovementComponent::SetInitialVelocity(Math::Vector2D initialVelocity)
{
	velocity = initialVelocity;
}
