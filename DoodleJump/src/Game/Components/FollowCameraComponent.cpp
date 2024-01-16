#include "FollowCameraComponent.h"
#include "Doodle.h"
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
		std::shared_ptr<MovementComponent> movement = doodle->GetMovementComponent();

	}
}
