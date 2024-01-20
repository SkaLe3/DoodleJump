#pragma once
#include "SceneComponent.h"
#include "Math/MyMath.h"

class CameraComponent : public SceneComponent
{
public:
	CameraComponent() = default;
	virtual void Start() override { SceneComponent::Start(); }
	virtual void Tick(double DeltaTime) override { SceneComponent::Tick(DeltaTime); }
	virtual void Destroy() override {}
public:
	void SetProjection(int32_t size);
	void SetViewportSize(uint32_t width, uint32_t height);
	Math::Vector2D GetCameraBounds();
	const Math::Mat4& GetProjection() const { return projection; }

protected:
	Math::Vector2D viewportSize;
	double aspectRatio = 1;
	double orthographicSize;
	Math::Mat4 projection = Math::Mat4(1.0);
};


