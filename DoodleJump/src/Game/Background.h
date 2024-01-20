#pragma once
#include "Entities/GameObject.h"

class Background : public GameObject
{
public:
	Background();
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;

public:
	std::shared_ptr<SpriteComponent> GetSpriteComponent() const { return spriteComponent; }

private:
	std::shared_ptr<SpriteComponent> spriteComponent;
};