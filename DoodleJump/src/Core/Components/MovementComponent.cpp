#include "MovementComponent.h"
#include "Math/Transform.h"
//#include "World/World.h"
#include "Math/FuncGeometric.h"
#include "Entities/GameObject.h"

void MovementComponent::Start()
{
	GameComponent::Start();
}

void MovementComponent::Tick(double deltaTime)
{
	GameComponent::Tick(deltaTime);
	Math::Transform& transform = owner->GetTransform();

	

}

void MovementComponent::AddForce(Math::Vector2D force)
{
	
}
