#pragma once
#include "Components/CameraComponent.h"

class FollowCameraComponent : public CameraComponent
{
public:
	FollowCameraComponent() = default;

	//~Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	//~End Object Interface

	void FollowEnable(bool bEnable);

private:
	bool m_bFollowEnabled = true;
};