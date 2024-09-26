#pragma once
#include "Entities/GameObject.h"
#include "Input/InputValue.h"

class MenuController : public GameObject
{
public:
	MenuController();
	~MenuController();

	//~ Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;
	//~ End Object Interface

	void Click(InputValue& value);

private:
	std::shared_ptr<CameraComponent> m_CameraComponent;
};