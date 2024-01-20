#include "MovementComponent.h"
#include "Math/Transform.h"
//#include "World/World.h"
#include "Math/FuncGeometric.h"
#include "Entities/GameObject.h"

//terstin
#include <iostream>

MovementComponent::MovementComponent()
{
	
	gravity = Math::Vector2D::ZeroVector;
	acceleration = Math::Vector2D::ZeroVector;
	velocity = Math::Vector2D::ZeroVector;
}

void MovementComponent::Start()
{
	GameComponent::Start();


}

void MovementComponent::Tick(double deltaTime)
{
	GameComponent::Tick(deltaTime);
	Math::Transform& transform = owner->GetTransform();


	acceleration += gravity;
	velocity += acceleration * 0.5 * deltaTime;

	transform.Translation += Math::Vector(velocity * deltaTime, 0);
	velocity += acceleration * 0.5 * deltaTime;

	GetOwner()->GetBoxComponent()->SetAcceleration(acceleration);
	GetOwner()->GetBoxComponent()->SetVelocity(velocity);
	GetOwner()->GetBoxComponent()->SetGravity(gravity);
	acceleration = Math::Vector2D::ZeroVector;


}



void MovementComponent::Destroy()
{
	GetScene()->DestroyTickComponent(GetScene()->GetComponent(this));
}

void MovementComponent::SetGravity(double gravityValue)
{
	gravity.y = gravityValue;
}

void MovementComponent::SetMaxSpeed(double speed)
{
	maxSpeed = speed;
}

void MovementComponent::OnCollision(double collisionTime)
{
	// Add remaining time to use instead of delta time when collision occurs
	owner->GetTransform().Translation += Math::Vector(owner->GetBoxComponent()->GetVelocity() * collisionTime, 0);
}
