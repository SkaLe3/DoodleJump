#include "GameObject.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include <cassert>

GameObject::GameObject() : m_Tag("")
{
	m_BoxComponent = CreateComponent<BoxComponent>();
	m_RootComponent = m_BoxComponent;
}

void GameObject::Start()
{
	if (auto box = m_BoxComponent.lock())
	{
		box->SetOwner(GetSelf());
	}
}

void GameObject::Tick(double deltaTime)
{

}

void GameObject::Destroy()
{
	GetScene()->DestroyGameObject(GetSelf());
	if (auto box = m_BoxComponent.lock())
		box->Destroy();
}

Math::Transform& GameObject::GetTransform()
{
	if (auto root = m_RootComponent.lock())
		return root->GetTransform();
	else
		assert(false);
}

Math::Transform GameObject::GetWorldTransform()
{
	if (auto root = m_RootComponent.lock())
		return root->GetWorldTransform();
	else
		assert(false);
}

std::shared_ptr<BoxComponent> GameObject::GetBoxComponent()
{
	return m_BoxComponent.lock();
}

Math::Vector2D GameObject::GetLocation()
{

	if (auto root = m_RootComponent.lock())
		return Math::Vector2D(root->GetWorldTransform().Translation);
	else
		return Math::Vector2D::ZeroVector;
}

void GameObject::SetLocation(const Math::Vector& location)
{
	if (auto box = m_BoxComponent.lock())
	box->GetTransform().Translation = location;
}

void GameObject::SetTag(const std::string& newTag)
{
	m_Tag = newTag;
}

std::string GameObject::GetTag()
{
	return m_Tag;
}

void GameObject::AttachToObject(std::weak_ptr<GameObject> parentObject)
{
	auto parent = parentObject.lock();
	if (!parent)
		return;
	if (GetSelf().lock() == parent)
		return;

	this->DetachFromObject();
	
	if (std::shared_ptr<SceneComponent> rootComp = GetRoot())
	{
		rootComp->SetupAttachment(parent->GetRoot());
	}
}

void GameObject::DetachFromObject()
{
	if (std::shared_ptr<SceneComponent> rootComp = GetRoot())
	{
		rootComp->DetachFromParent();
	}
}
