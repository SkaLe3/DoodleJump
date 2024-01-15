#pragma once
#include "Entities/GameObject.h"
#include "Input/InputValue.h"

class DoodleMovementComponent;
class SpriteComponent;
class CameraComponent;

class Doodle : public GameObject
{
public:
	Doodle();
	virtual void Start() override;
	virtual void Tick(double DeltaTime) override;

	std::shared_ptr<SpriteComponent> GetSpriteComponent() const { return spriteComponent; }
	std::shared_ptr<DoodleMovementComponent> GetMovementComponent() const { return movementComponent; }

public:
	void Move(InputValue& value);

private:
	std::shared_ptr<SpriteComponent> spriteComponent;
	std::shared_ptr<CameraComponent> cameraComponent;
	std::shared_ptr<DoodleMovementComponent> movementComponent;
};