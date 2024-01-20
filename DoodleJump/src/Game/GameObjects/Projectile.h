#pragma once
#include "Entities/GameObject.h"
#include "Components/ProjectileMovementComponent.h"
#include "Components/SpriteComponent.h"

#include <memory>

class Projectile : public GameObject
{
public:
	Projectile();

	virtual void Start() override;
	virtual void Tick(double DeltaTime) override;
private:
	std::shared_ptr<SpriteComponent> spriteComponent;
	std::shared_ptr<ProjectileMovementComponent> movementComponent;
};