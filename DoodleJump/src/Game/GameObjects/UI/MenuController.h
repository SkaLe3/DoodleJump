#pragma once
#include "Entities/GameObject.h"
#include "Input/InputValue.h"

class MenuController : public GameObject
{
public:
	MenuController();
	virtual void Start() override;
	virtual void Tick(double deltatime) override;
	virtual void Destroy() override;

public:
	void Click(InputValue& value);

private:
	std::shared_ptr<CameraComponent> cameraComponent;
};