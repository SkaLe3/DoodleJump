#pragma once
#include "Components/CameraComponent.h"

class FollowCameraComponent : public CameraComponent
{
public:
	FollowCameraComponent() = default;
	virtual void Start() override;
	virtual void Tick(double DeltaTime) override;
};