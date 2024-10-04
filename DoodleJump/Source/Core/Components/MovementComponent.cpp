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
	if (auto owner = m_Owner.lock())
	{
		Math::Transform& transform = owner->GetTransform();

		m_Acceleration += m_Gravity;
		m_Velocity += m_Acceleration * 0.5 * deltaTime;
		transform.Translation += Math::Vector(m_Velocity * deltaTime, 0);
		m_Velocity += m_Acceleration * 0.5 * deltaTime;

		if (auto box = owner->GetBoxComponent())
		{
			box->SetAcceleration(m_Acceleration);
			box->SetVelocity(m_Velocity);
			box->SetGravity(m_Gravity);
		}
		m_Acceleration = Math::Vector2D::ZeroVector;
	}
}


void MovementComponent::Destroy()
{
	GetScene()->DestroyTickComponent(GetSelf());
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
	auto owner = GetOwner().lock();
	auto box = owner->GetBoxComponent();
	if (owner && box )
	{
		owner->GetTransform().Translation += Math::Vector(box->GetVelocity() * collisionTime, 0);
	}
}
