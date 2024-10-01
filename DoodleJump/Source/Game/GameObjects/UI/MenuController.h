#pragma once
#include "Core/Entities/GameObject.h"
#include "Core/Input/InputValue.h"

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
	inline std::shared_ptr<CameraComponent> GetCameraComponent() { return m_CameraComponent.lock();}

private:
	std::weak_ptr<CameraComponent> m_CameraComponent;
};