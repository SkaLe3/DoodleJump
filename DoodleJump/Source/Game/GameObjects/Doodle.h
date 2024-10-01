#pragma once
#include "Core/Entities/GameObject.h"
#include "Core/Input/InputValue.h"

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

	std::shared_ptr<SpriteComponent> GetSpriteComponent() const { return m_SpriteComponent.lock(); }
	std::shared_ptr<DoodleMovementComponent> GetMovementComponent() const { return m_MovementComponent.lock(); }
	std::shared_ptr<CameraComponent> GetCameraComponent() const { return m_CameraComponent.lock(); }
	Math::Vector2D GetVelocity() const;
	int32_t GetLifesCount();
	int32_t GetJumpsCount();
	inline int32_t GetLookHDirection() { return m_LookHDirection; }
	inline bool IsJumping() { return m_bJumping; }
	inline bool IsShooting() { return m_bShooting; }

	void AddMovementInput(Math::Vector2D direction);
	void Jump();
	void DisableInput();
	void EnableInput();
	void DisablePhysicsCollision();
	void EnableCollision();

	void ResetJumpsCount();
	std::shared_ptr<ImmunityAbility> GetImmunity();

	void Move(InputValue& value);
	void Shoot(InputValue& value);

	void OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime);

private:
	std::weak_ptr<SpriteComponent> m_SpriteComponent;
	std::weak_ptr<CameraComponent> m_CameraComponent;
	std::weak_ptr<DoodleMovementComponent> m_MovementComponent;

	std::weak_ptr<GameObject> m_Crosshair;
	std::weak_ptr<ImmunityAbility> m_Immunity;

	double m_DefaultJumpVelocity = 70;
	int32_t m_LifesCount = 5;
	int32_t m_JumpsCount = 0;
	double m_ImmunityTimer;

	bool m_bInputEnabled = true;
	bool m_bPhysicsCollisionEnabled = true;

	int32_t m_LookHDirection = -1;
	bool m_bJumping = false;
	bool m_bShooting = false;
	double m_JumpTimer = 0;
	double m_ShootTimer = 0;

};