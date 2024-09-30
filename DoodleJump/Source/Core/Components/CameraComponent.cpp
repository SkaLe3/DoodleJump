#include "CameraComponent.h"
#include "World/Scene.h"
#include "World/World.h"

#include <algorithm>

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
	m_OrthographicSize = _size;
	double left = -m_OrthographicSize * 0.5;
	double right = m_OrthographicSize * 0.5;
	double bottom = -m_OrthographicSize * m_AspectRatio * 0.5;
	double top = m_OrthographicSize * m_AspectRatio * 0.5;

	m_Projection = Math::Orthographic(left, right, bottom, top, 0, m_ViewportSize.x, m_ViewportSize.y, 0);
}

void CameraComponent::SetViewportSize(uint32_t width, uint32_t height)
{
	m_ViewportSize = { (double)width, (double)height };
	m_AspectRatio = (double)height / (double)width;
}

Math::Vector2D CameraComponent::GetCameraBounds()
{
	return Math::Vector2D(m_OrthographicSize, m_OrthographicSize * m_AspectRatio);
}

const Math::Mat4& CameraComponent::GetProjection() const
{
	return m_Projection;
}

const double CameraComponent::GetAspectRatio() const
{
	return m_AspectRatio;
}

