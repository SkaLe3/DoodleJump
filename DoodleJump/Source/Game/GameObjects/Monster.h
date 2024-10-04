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

	void OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime);
	std::shared_ptr<SpriteComponent> GetSpriteComponent() { return m_SpriteComponent.lock(); }

private:
	std::weak_ptr<SpriteComponent> m_SpriteComponent;
};