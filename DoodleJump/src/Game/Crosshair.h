#pragma once
#include "Entities/GameObject.h"
#include <memory>

class SpriteComponent;

class Crosshair : public GameObject
{
public:
	Crosshair();
	virtual void Start() override;
	virtual void Tick(double DeltaTime) override;

public:
	std::shared_ptr<SpriteComponent> GetSpriteComponent() const { return spriteComponent; }

private:
	std::shared_ptr<SpriteComponent> spriteComponent;
};