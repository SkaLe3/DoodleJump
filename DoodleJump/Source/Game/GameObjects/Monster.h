#pragma once
#include "Core/Entities/GameObject.h"

class SpriteComponent;

class Monster : public GameObject
{
public:
	Monster();
	~Monster();

	//~ Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;
	//~ End Object Interface

	void Kill();

	void OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime);
	std::shared_ptr<SpriteComponent> GetSpriteComponent() { return m_SpriteComponent.lock(); }
	inline bool IsDying() { return m_bDying; }
private:
	std::weak_ptr<SpriteComponent> m_SpriteComponent;
	bool m_bDying = false;
	double m_DeathTimer = 0;
	double m_DeathTime = 0.2;
};