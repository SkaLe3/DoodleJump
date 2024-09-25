#pragma once
#include "Entities/GameObject.h"
#include <memory>

class SpriteComponent;

class Crosshair : public GameObject
{
public:
	Crosshair();
	~Crosshair();
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;

public:
	std::shared_ptr<SpriteComponent> GetSprite() const { return spriteComponent; }

private:
	std::shared_ptr<SpriteComponent> spriteComponent;
};