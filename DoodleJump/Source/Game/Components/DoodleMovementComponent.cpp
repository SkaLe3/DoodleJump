#include "DoodleMovementComponent.h"
#include "Entities/GameObject.h"

DoodleMovementComponent::DoodleMovementComponent() : MovementComponent(), m_JumpVelocity(20)
{
}

void DoodleMovementComponent::Start()
{
	MovementComponent::Start();
}

void DoodleMovementComponent::Tick(double deltaTime)
{
	MovementComponent::Tick(deltaTime);

	m_Velocity.x = 0;
}

void DoodleMovementComponent::AddMovementInput(Math::Vector2D direction)
{
	m_Velocity.x = direction.x * m_MaxSpeed;
}

void DoodleMovementComponent::Jump()
{
	m_Velocity.y = m_JumpVelocity;
}

void DoodleMovementComponent::SetJumpVelocity(double velocity)
{
	m_JumpVelocity = velocity;
}
