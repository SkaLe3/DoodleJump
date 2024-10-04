#pragma once
#include "GameComponent.h"


class SceneComponent : public GameComponent
{

public:
	// Transform is relative
	Math::Transform& GetTransform();
	Math::Mat4 GetTransformMatrix();
	void SetupAttachment(std::weak_ptr<SceneComponent> component);
	void DetachFromParent();

protected:
	// Transform is relative to parent
	Math::Transform m_Transform;

	std::weak_ptr<SceneComponent> m_Parent;
};