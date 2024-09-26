#include "SceneComponent.h"

Math::Transform& SceneComponent::GetTransform()
{
	return m_Transform;
}

Math::Mat4 SceneComponent::GetTransformMatrix()
{
	if (m_Parent)
		return m_Parent->GetTransformMatrix() * m_Transform.ToMat4();
	return m_Transform.ToMat4();
}

void SceneComponent::SetupAttachment(std::shared_ptr<SceneComponent> component)
{
	m_Parent = component;
}

void SceneComponent::DetachFromParent()
{
	m_Parent = nullptr;
}

