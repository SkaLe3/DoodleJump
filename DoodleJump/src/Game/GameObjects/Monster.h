#pragma once
#include "Entities/GameObject.h"

class SpriteComponent;

class Monster : public GameObject
{
public:
	Monster();
	virtual void Start() override;
	virtual void Tick(double DeltaTime) override;
	virtual void Destroy() override;

public:
	void OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime);
private:
	std::shared_ptr<SpriteComponent> spriteComponent;
};