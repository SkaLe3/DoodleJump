#pragma once
#include "Components/GameComponent.h"
#include <memory>
#include <vector>

class SpriteComponent;
class SceneComponent;
class MySprite;

class NumberComponent : public GameComponent
{
public:
	NumberComponent();
	virtual void Start() override;
	virtual void Tick(double DeltaTime) override;
	virtual void Destroy() override;

	void Update(int32_t number);
	void AddDigit(std::shared_ptr<SpriteComponent> sprite);
	std::vector<std::shared_ptr<SpriteComponent>>& GetSprites();

private:
	std::vector<std::shared_ptr<SpriteComponent>> sprites;
	std::vector<std::shared_ptr<MySprite>> digits;
};