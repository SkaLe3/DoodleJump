#include "FollowCameraComponent.h"
#include "GameObjects/DoodleController.h"
#include "DoodleMovementComponent.h"

void FollowCameraComponent::Start()
{
	CameraComponent::Start();
}

void FollowCameraComponent::Tick(double deltaTime)
{
	CameraComponent::Tick(deltaTime);
	if (!m_bFollowEnabled)
		return;
	if (auto owner = m_Owner.lock())
	{

		std::shared_ptr<DoodleController> doodle = dynamic_pointer_cast<DoodleController>(owner);
		if (doodle)
		{
			Math::Vector2D doodleLocation = doodle->GetLocation();
			if (doodleLocation.y >= GetTransform().Translation.y)
				GetTransform().Translation.y = doodleLocation.y;
		}
	}
}

void FollowCameraComponent::FollowEnable(bool bEnable)
{
	m_bFollowEnabled = bEnable;
}
