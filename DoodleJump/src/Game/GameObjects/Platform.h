#pragma once
#include "Entities/GameObject.h"

class Platform : public GameObject
{
public:
	Platform();
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;

public:
	std::shared_ptr<SpriteComponent> GetSpriteComponent() const { return spriteComponent; }

private:
	std::shared_ptr<SpriteComponent> spriteComponent;
};