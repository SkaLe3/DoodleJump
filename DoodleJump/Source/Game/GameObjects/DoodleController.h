#pragma once
#include "Core/Entities/GameObject.h"
#include "Core/Input/InputValue.h"
#include "GameObjects/Doodle.h"

class CameraComponent;

class DoodleController : public Doodle
{
public:
	DoodleController();

	//~ Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;
	//~ End Object Interface
	
	std::shared_ptr<CameraComponent> GetCameraComponent() const { return m_CameraComponent.lock(); }
	int32_t GetLifesCount();
	int32_t GetJumpsCount();

	void AddMovementInput(Math::Vector2D direction);
	void DisableInput();
	void EnableInput();
	void ResetJumpsCount();

	void Move(InputValue& value);
	void Shoot(InputValue& value);

private:	
	std::weak_ptr<CameraComponent> m_CameraComponent;	
	std::weak_ptr<GameObject> m_Crosshair;

	bool m_bInputEnabled = true;
};