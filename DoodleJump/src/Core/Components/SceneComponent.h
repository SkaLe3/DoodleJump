#pragma once
#include "Math/MyMath.h"
#include "GameComponent.h"
#include "Math/Matrix4.h"

class SceneComponent : public GameComponent
{
public:
	SceneComponent() = default;

	virtual void Start() override { GameComponent::Start(); }
	virtual void Tick(double DeltaTime) override { GameComponent::Tick(DeltaTime); }
public:
	// Transform is relative
	Math::Transform& GetTransform() { return transform; }
	Math::Mat4 GetTransformMatrix()
	{
 		if (parent)
 			return parent->GetTransformMatrix() * transform.ToMat4();
 		return transform.ToMat4();
	}
	void SetupAttachment(std::shared_ptr<SceneComponent> _parent) { parent = _parent; }
	void DetachFromParent() { parent = nullptr; }

protected:
	// Transform relative to parent
	Math::Transform transform;

	std::shared_ptr<SceneComponent> parent;
};