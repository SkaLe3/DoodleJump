#include "ProjectileMovementComponent.h"

ProjectileMovementComponent::ProjectileMovementComponent() : MovementComponent()
{

}

void ProjectileMovementComponent::Start()
{
	MovementComponent::Start();
}

void ProjectileMovementComponent::Tick(double deltaTime)
{
	MovementComponent::Tick(deltaTime);
}

void ProjectileMovementComponent::SetInitialVelocity(Math::Vector2D initialVelocity)
{
	m_Velocity = initialVelocity;
}
