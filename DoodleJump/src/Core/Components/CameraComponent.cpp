#include "CameraComponent.h"

void CameraComponent::SetProjection(int32_t _size)
{
	orthographicSize = _size;
	double left = -orthographicSize * aspectRatio * 0.5;
	double right = orthographicSize * aspectRatio * 0.5;
	double bottom = -orthographicSize * 0.5;
	double top = orthographicSize * 0.5;

	projection = Math::Orthographic(left, right, bottom, top, 0, viewportSize.x, viewportSize.y, 0);
}

void CameraComponent::SetViewportSize(uint32_t width, uint32_t height)
{
	viewportSize = { (double)width, (double)height };
	aspectRatio = (double)width / (double)height;
}

Math::Vector2D CameraComponent::GetCameraBounds()
{
	return Math::Vector2D(orthographicSize * aspectRatio, orthographicSize);
}

