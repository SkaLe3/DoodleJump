#include "FollowCameraComponent.h"
#include "GameObjects/Doodle.h"
#include "DoodleMovementComponent.h"

void FollowCameraComponent::Start()
{
	CameraComponent::Start();
}

void FollowCameraComponent::Tick(double DeltaTime)
{
	CameraComponent::Tick(DeltaTime);

	std::shared_ptr<Doodle> doodle = dynamic_pointer_cast<Doodle>(owner);
	if (doodle)
	{
		Math::Vector2D doodleLocation = doodle->GetLocation();
		if (doodleLocation.y >= GetTransform().Translation.y)
			GetTransform().Translation.y = doodleLocation.y;
	}
}
