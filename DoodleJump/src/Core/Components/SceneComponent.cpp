#include "SceneComponent.h"

Math::Transform& SceneComponent::GetTransform()
{
	return transform;
}

Math::Mat4 SceneComponent::GetTransformMatrix()
{
	if (parent)
		return parent->GetTransformMatrix() * transform.ToMat4();
	return transform.ToMat4();
}

void SceneComponent::SetupAttachment(std::shared_ptr<SceneComponent> component)
{
	parent = component;
}

void SceneComponent::DetachFromParent()
{
	parent = nullptr;
}
