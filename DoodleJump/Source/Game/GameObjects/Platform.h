#pragma once
#include "Entities/GameObject.h"

class ProjectileMovementComponent;

class Platform : public GameObject
{
public:
	Platform();
	~Platform();

	//~ Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;
	//~ End Object Interface

	void Pass();
	bool IsPassed();
	void Reset();

	void StartMovement();
	void StopMovement();
	void ReflectMovement();

	std::shared_ptr<SpriteComponent> GetSpriteComponent() const { return m_SpriteComponent.lock(); }
	std::shared_ptr<ProjectileMovementComponent> GetMovementComponent() const { return m_MovementComponent.lock(); }

	void OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime);

protected:
	std::weak_ptr<SpriteComponent> m_SpriteComponent;
	std::weak_ptr<ProjectileMovementComponent> m_MovementComponent;
	bool m_bPassed;
	uint32_t m_MoveSpeed = 6.5;
};