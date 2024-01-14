#pragma once
#include "Math/MyMath.h"
#include "GameComponent.h"
#include "Math/Matrix4.h"

class SceneComponent : public GameComponent
{
public:
	SceneComponent() = default;
	Math::Transform& GetTransform() { return transform; }
	Math::Mat4 GetTransformMatrix()
	{
// 		if (parent)
// 			return parent->GetTransformMatrix() * transform.ToMat4();
// 		return transform.ToMat4();
		return Math::Mat4();
	}
	void SetupAttachment(std::shared_ptr<SceneComponent> _parent) { parent = _parent; }

protected:
	// Transform relative to parent
	Math::Transform transform;

	std::shared_ptr<SceneComponent> parent;
};