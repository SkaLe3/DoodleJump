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

	void Activate();
	inline bool IsActive() { return m_bActivated; }

	void DisableCollision();
	double GetTime();
	inline bool IsEnding() { return m_bEnding; }

	inline std::shared_ptr<SpriteComponent> GetSpriteComponent() { return m_SpriteComponent.lock(); }

private:
	std::weak_ptr<SpriteComponent> m_SpriteComponent;
	double m_AbilityTime = 20;
	double m_EndTime = 17;
	double m_ImmunityTimer = 0;
	bool m_bActivated = false;
	bool m_bEnding = false;
};