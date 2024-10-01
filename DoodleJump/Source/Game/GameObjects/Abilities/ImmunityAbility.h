#pragma once
#include "Core/Entities/GameObject.h"

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
	inline std::shared_ptr<SpriteComponent> GetSpriteComponent() { return m_SpriteComponent.lock(); }

private:
	std::weak_ptr<SpriteComponent> m_SpriteComponent;
	double m_AbilityTime = 20;
};