#pragma once
#include "SceneComponent.h"

class CameraComponent : public SceneComponent
{
public:
	CameraComponent() = default;

	//~Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;
	//~End Object Interface

	Math::Vector2D GetCameraBounds();
	const Math::Mat4& GetProjection() const;
	const double GetAspectRatio() const;
	void SetProjection(int32_t size);
	void SetViewportSize(uint32_t width, uint32_t height);

protected:
	double m_AspectRatio = 1;
	double m_OrthographicSize;

	Math::Mat4 m_Projection = Math::Mat4(1.0);
	Math::Vector2D m_ViewportSize;
};


