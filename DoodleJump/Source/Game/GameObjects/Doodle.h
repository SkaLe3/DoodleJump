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
	~Doodle();

	//~ Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;
	//~ End Object Interface

	std::shared_ptr<SpriteComponent> GetSprite() const { return m_SpriteComponent; }
	std::shared_ptr<DoodleMovementComponent> GetMovementComponent() const { return m_MovementComponent; }
	Math::Vector2D GetVelocity() const;
	int32_t GetLifesCount();
	int32_t GetJumpsCount();

	void AddMovementInput(Math::Vector2D direction);
	void Jump();
	void DisableInput();
	void EnableInput();
	void DisablePhysicsCollision();
	void EnableCollision();

	void ResetJumpsCount();
	bool HasImmunity();

	void Move(InputValue& value);
	void Shoot(InputValue& value);

	void OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime);

private:
	std::shared_ptr<SpriteComponent> m_SpriteComponent;
	std::shared_ptr<CameraComponent> m_CameraComponent;
	std::shared_ptr<DoodleMovementComponent> m_MovementComponent;

	std::shared_ptr<GameObject> m_Crosshair;
	std::shared_ptr<ImmunityAbility> m_Immunity = nullptr;

	double m_DefaultJumpVelocity = 70;
	int32_t m_LifesCount = 5;
	int32_t m_JumpsCount = 0;
	double m_ImmunityTimer;

	bool m_bInputEnabled = true;
	bool m_bPhysicsCollisionEnabled = true;
};