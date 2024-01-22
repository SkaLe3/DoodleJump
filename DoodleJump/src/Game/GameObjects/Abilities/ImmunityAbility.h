#pragma once

#include "Entities/GameObject.h"
#include <memory>
class SpriteComponent;

class ImmunityAbility : public GameObject
{
public:
	ImmunityAbility();

	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;

	void DisableCollision();
	double GetTime();

private:
	std::shared_ptr<SpriteComponent> spriteComponent;

	double abilityTime = 20;
};