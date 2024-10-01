#pragma once
#include "Core/Entities/GameObject.h"


class SpriteComponent;
class ProjectileMovementComponent;

class Projectile : public GameObject
{
public:
	Projectile();
	~Projectile();

	//~ Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;
	//~ End Object Interface

	void Launch(Math::Vector2D direction, double speed);
	void OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime);

private:
	std::shared_ptr<SpriteComponent> m_SpriteComponent;
	std::shared_ptr<ProjectileMovementComponent> m_MovementComponent;

	double m_AutoDestroyTimer = 0;
};