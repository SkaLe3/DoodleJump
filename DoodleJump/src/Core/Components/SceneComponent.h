#pragma once
#include "GameComponent.h"
#include "Math/Matrix4.h"

class SceneComponent : public GameComponent
{

public:
	// Transform is relative
	Math::Transform& GetTransform();
	Math::Mat4 GetTransformMatrix();
	void SetupAttachment(std::shared_ptr<SceneComponent> component);
	void DetachFromParent();

protected:
	// Transform relative to parent
	Math::Transform transform;

	std::shared_ptr<SceneComponent> parent;
};