#include "SceneComponent.h"

Math::Transform& SceneComponent::GetTransform()
{
	return m_Transform;
}

Math::Mat4 SceneComponent::GetTransformMatrix()
{
	if (auto parent = m_Parent.lock())
		return parent->GetTransformMatrix() * m_Transform.ToMat4();
	return m_Transform.ToMat4();
}

void SceneComponent::SetupAttachment(std::weak_ptr<SceneComponent> component)
{
	m_Parent = component;
}

void SceneComponent::DetachFromParent()
{
	m_Parent.reset();
}

