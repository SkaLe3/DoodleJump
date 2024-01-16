#include "GameObject.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"

// testins
#include <iostream>
GameObject::GameObject()
{
	boxComponent = CreateComponent<BoxComponent>();
	rootComponent = boxComponent;
}


void GameObject::Start()
{
	boxComponent->SetOwner(GetScene()->GetObject(this));
}

void GameObject::Tick(double DeltaTime)
{

}

Math::Transform& GameObject::GetTransform()
{
	return rootComponent->GetTransform();
}

Math::Vector2D GameObject::GetLocation()
{
	return Math::Vector2D(rootComponent->GetTransform().Translation);
}
