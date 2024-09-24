#pragma once
#include "Entities/GameObject.h"


#include <memory>

class SpriteComponent;
class ProjectileMovementComponent;

class Projectile : public GameObject
{
public:
	Projectile();
	~Projectile();

	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;
public:
	void OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime);
	void Launch(Math::Vector2D direction, double speed);
private:
	std::shared_ptr<SpriteComponent> spriteComponent;
	std::shared_ptr<ProjectileMovementComponent> movementComponent;

	double autoDestroyTimer = 0;
};