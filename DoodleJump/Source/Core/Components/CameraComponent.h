#pragma once
#include "SceneComponent.h"
#include "Math/MyMath.h"

class CameraComponent : public SceneComponent
{
public:
	CameraComponent() = default;
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;

public:
	void SetProjection(int32_t size);
	void SetViewportSize(uint32_t width, uint32_t height);
	Math::Vector2D GetCameraBounds();
	const Math::Mat4& GetProjection() const;

protected:
	double aspectRatio = 1;
	double orthographicSize;

	Math::Mat4 projection = Math::Mat4(1.0);
	Math::Vector2D viewportSize;
};


