#pragma once
#include "Components/GameComponent.h"
#include <memory>
#include <vector>

class SpriteComponent;
class MySprite;

class NumberComponent : public GameComponent
{
public:
	NumberComponent();
	virtual void Start() override;
	virtual void Tick(double DeltaTime) override;

private:
	std::vector<std::shared_ptr<SpriteComponent>> sprites;
	std::vector<std::shared_ptr<MySprite>> digits;
};