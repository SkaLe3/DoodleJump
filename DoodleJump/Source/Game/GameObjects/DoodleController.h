#pragma once
#include "Core/Entities/GameObject.h"
#include "Core/Input/InputValue.h"
#include "GameObjects/Doodle.h"

class CameraObject;

class DoodleController : public Doodle
{
public:
	DoodleController();

	//~ Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;
	//~ End Object Interface

	int32_t GetLifesCount();
	int32_t GetJumpsCount();
	std::weak_ptr<CameraObject> GetCamera() { return m_Camera; }

	void AddMovementInput(Math::Vector2D direction);
	void DisableInput();
	void EnableInput();
	void ResetJumpsCount();

	void Move(InputValue& value);
	void Shoot(InputValue& value);

private:
	std::weak_ptr<GameObject> m_Crosshair;
	std::weak_ptr<CameraObject> m_Camera;

	bool m_bInputEnabled = true;
};