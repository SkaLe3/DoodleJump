#include "GameObject.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"

GameObject::GameObject() : m_Tag("")
{
	m_BoxComponent = CreateComponent<BoxComponent>();
	m_RootComponent = m_BoxComponent;
}

void GameObject::Start()
{
	m_BoxComponent->SetOwner(GetScene()->GetObject(this));
}

void GameObject::Tick(double deltaTime)
{

}

void GameObject::Destroy()
{
	GetScene()->DestroyGameObject(GetScene()->GetObject(this));
	m_BoxComponent->Destroy();
}

Math::Transform& GameObject::GetTransform()
{
	return m_RootComponent->GetTransform();
}

std::shared_ptr<BoxComponent> GameObject::GetBoxComponent()
{
	return m_BoxComponent;
}

Math::Vector2D GameObject::GetLocation()
{
	return Math::Vector2D(m_RootComponent->GetTransform().Translation);
}

void GameObject::SetLocation(const Math::Vector& location)
{
	m_BoxComponent->GetTransform().Translation = location;
}

void GameObject::SetTag(const std::string& newTag)
{
	m_Tag = newTag;
}

std::string GameObject::GetTag()
{
	return m_Tag;
}
