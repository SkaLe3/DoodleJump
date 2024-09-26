#pragma once
#include "Entities/GameObject.h"
#include <memory>

class SpriteComponent;

class ImmunityAbility : public GameObject
{
public:
	ImmunityAbility();
	~ImmunityAbility();

	//~ Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;
	//~ End Object Interface

	void DisableCollision();
	double GetTime();

private:
	std::shared_ptr<SpriteComponent> m_SpriteComponent;
	double m_AbilityTime = 20;
};