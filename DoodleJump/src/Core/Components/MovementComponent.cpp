#include "MovementComponent.h"
#include "Math/Transform.h"
//#include "World/World.h"
#include "Math/FuncGeometric.h"
#include "Entities/GameObject.h"

//terstin
#include <iostream>

MovementComponent::MovementComponent()
{
	
	gravity = { 0, -10 };
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

// void MovementComponent::AddForce(Math::Vector2D force)
// {
// 	acceleration += force;
// 	GetOwner()->GetBoxComponent()->SetAcceleration(acceleration);
// }


void MovementComponent::SetGravity(double gravityValue)
{
	gravity.y = gravityValue;
}

void MovementComponent::SetMaxSpeed(double speed)
{
	maxSpeed = speed;
}
