#pragma once
#include "Entities/GameObject.h"
#include "Input/InputValue.h"
#include "Math/Vector2D.h"

class DoodleMovementComponent;
class SpriteComponent;
class CameraComponent;
class ImmunityAbility;

class Doodle : public GameObject
{
public:
	Doodle();
	virtual void Start() override;
	virtual void Tick(double DeltaTime) override;
	virtual void Destroy() override;

	std::shared_ptr<SpriteComponent> GetSprite() const { return spriteComponent; }
	std::shared_ptr<DoodleMovementComponent> GetMovementComponent() const { return movementComponent; }

	Math::Vector2D GetVelocity() const;

	void AddMovementInput(Math::Vector2D direction);
	void Jump();
	void DisableInput();
	void EnableInput();
	void DisablePhysicsCollision();
	void EnableCollision();

	int32_t GetLifesCount();
	int32_t GetJumpsCount();
	void ResetJumpsCount();

	bool HasImmunity();
public:
	void Move(InputValue& value);
	void Shoot(InputValue& value);

	void OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime);


private:
	std::shared_ptr<SpriteComponent> spriteComponent;
	std::shared_ptr<CameraComponent> cameraComponent;
	std::shared_ptr<DoodleMovementComponent> movementComponent;

	std::shared_ptr<GameObject> crosshair;

	double defaultJumpVelocity = 70;

	bool bInputEnabled = true;
	bool bPhysicsCollisionEnabled = true;

	int32_t lifesCount = 5;
	int32_t jumpsCount = 0;

	double immunityTimer;
	std::shared_ptr<ImmunityAbility> immunity = nullptr;
};