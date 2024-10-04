#pragma once
#include "Core/Entities/GameObject.h"

class DoodleMovementComponent;
class SpriteComponent;
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

	 Math::Vector2D GetVelocity() const;
	 inline std::shared_ptr<ImmunityAbility> GetImmunity() { return m_Immunity.lock(); }
	 inline int32_t GetLookHDirection() { return m_LookHDirection; }
	 inline bool IsJumping() { return m_bJumping; }
	 inline bool IsShooting() { return m_bShooting; }

	 void Jump();

	 void DisablePhysicsCollision();
	 void EnableCollision();  
	 void OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime);
protected:
	std::weak_ptr<SpriteComponent> m_SpriteComponent;
	std::weak_ptr<DoodleMovementComponent> m_MovementComponent;
	std::weak_ptr<ImmunityAbility> m_Immunity;

	double m_DefaultJumpVelocity = 70;
	bool m_bPhysicsCollisionEnabled = true;
	int32_t m_LookHDirection = -1;
	bool m_bJumping = false;
	bool m_bShooting = false;
	double m_JumpTimer = 0;
	double m_ShootTimer = 0;
	double m_ImmunityTimer;
	int32_t m_LifesCount = 5;
	int32_t m_JumpsCount = 0;
};

