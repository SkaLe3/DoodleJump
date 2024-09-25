#include "CameraComponent.h"
#include "World/Scene.h"
#include "World/World.h"

void CameraComponent::Start()
{
}

void CameraComponent::Tick(double deltaTime)
{
}


void CameraComponent::Destroy()
{
	GetScene()->DestroyTickComponent(GetScene()->GetComponent(this));
}

void CameraComponent::SetProjection(int32_t _size)
{
	orthographicSize = _size;
	double left = -orthographicSize * 0.5;
	double right = orthographicSize * 0.5;
	double bottom = -orthographicSize * aspectRatio * 0.5;
	double top = orthographicSize * aspectRatio * 0.5;

	projection = Math::Orthographic(left, right, bottom, top, 0, viewportSize.x, viewportSize.y, 0);
}

void CameraComponent::SetViewportSize(uint32_t width, uint32_t height)
{
	viewportSize = { (double)width, (double)height };
	aspectRatio = (double)height / (double)width;
}

Math::Vector2D CameraComponent::GetCameraBounds()
{
	return Math::Vector2D(orthographicSize, orthographicSize * aspectRatio);
}

const Math::Mat4& CameraComponent::GetProjection() const
{
	return projection;
}

