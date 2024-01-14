#include "GameObject.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"


GameObject::GameObject()
{
	boxComponent = CreateComponent<BoxComponent>();
	rootComponent = boxComponent;
}


Math::Transform& GameObject::GetTransform() const
{
	return rootComponent->GetTransform();
}
