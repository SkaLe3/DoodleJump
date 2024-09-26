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

	//~Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;
	//~End Object Interface

	void Update(int32_t number);
	void AddDigit(std::shared_ptr<SpriteComponent> sprite);
	std::vector<std::shared_ptr<SpriteComponent>>& GetSprites();

private:
	std::vector<std::shared_ptr<SpriteComponent>> m_Sprites;
	std::vector<std::shared_ptr<MySprite>> m_Digits;
};