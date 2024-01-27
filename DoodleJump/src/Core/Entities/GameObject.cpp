#include "GameObject.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"

GameObject::GameObject() : tag("")
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

void GameObject::Destroy()
{
	GetScene()->DestroyGameObject(GetScene()->GetObject(this));
	boxComponent->Destroy();
}

Math::Transform& GameObject::GetTransform()
{
	return rootComponent->GetTransform();
}

std::shared_ptr<BoxComponent> GameObject::GetBoxComponent()
{
	return boxComponent;
}

Math::Vector2D GameObject::GetLocation()
{
	return Math::Vector2D(rootComponent->GetTransform().Translation);
}

void GameObject::SetLocation(const Math::Vector& location)
{
	boxComponent->GetTransform().Translation = location;
}

void GameObject::SetTag(const std::string& newTag)
{
	tag = newTag;
}

std::string GameObject::GetTag()
{
	return tag;
}
