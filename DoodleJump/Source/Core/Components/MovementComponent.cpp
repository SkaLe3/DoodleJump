#include "MovementComponent.h"
#include "Entities/GameObject.h"


MovementComponent::MovementComponent()
{
	m_Gravity = Math::Vector2D::ZeroVector;
	m_Acceleration = Math::Vector2D::ZeroVector;
	m_Velocity = Math::Vector2D::ZeroVector;
}

void MovementComponent::Start()
{

}

void MovementComponent::Tick(double deltaTime)
{
	Math::Transform& transform = m_Owner->GetTransform();

	m_Acceleration += m_Gravity;
	m_Velocity += m_Acceleration * 0.5 * deltaTime;
	transform.Translation += Math::Vector(m_Velocity * deltaTime, 0);
	m_Velocity += m_Acceleration * 0.5 * deltaTime;

	GetOwner()->GetBoxComponent()->SetAcceleration(m_Acceleration);
	GetOwner()->GetBoxComponent()->SetVelocity(m_Velocity);
	GetOwner()->GetBoxComponent()->SetGravity(m_Gravity);
	m_Acceleration = Math::Vector2D::ZeroVector;
}


void MovementComponent::Destroy()
{
	GetScene()->DestroyTickComponent(GetScene()->GetComponent(this));
}

void MovementComponent::SetGravity(double gravityValue)
{
	m_Gravity.y = gravityValue;
}

void MovementComponent::SetMaxSpeed(double speed)
{
	m_MaxSpeed = speed;
}

void MovementComponent::OnCollision(double collisionTime)
{
	// TODO: Add remaining time to use instead of delta time when collision occurs
	m_Owner->GetTransform().Translation += Math::Vector(m_Owner->GetBoxComponent()->GetVelocity() * collisionTime, 0);
}
