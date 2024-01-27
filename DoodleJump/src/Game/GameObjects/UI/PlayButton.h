#pragma once
#include "Entities/GameObject.h"

class SpriteComponent;

class PlayButton : public GameObject
{
public:
	PlayButton();
	virtual void Start() override;
	virtual void Tick(double DeltaTime) override;
	virtual void Destroy() override;

	void Click();

	std::shared_ptr<SpriteComponent> GetSprite() const { return spriteComponent; }

private:
	std::shared_ptr<SpriteComponent> spriteComponent;
};