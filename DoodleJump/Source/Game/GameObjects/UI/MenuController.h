#pragma once
#include "Core/Entities/GameObject.h"
#include "Core/Input/InputValue.h"

class CameraObject;

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
	inline std::weak_ptr<CameraObject> GetCamera() { return m_Camera;}

private:
	std::weak_ptr<CameraObject> m_Camera;
};