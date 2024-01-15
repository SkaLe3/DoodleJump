#pragma once
#include "Framework.h"

#include "SceneComponent.h"
#include <iostream>

// TESTING
#include <iostream>
class SpriteComponent : public SceneComponent
{
public:
	SpriteComponent() = default;

	virtual void Start() override {}
	virtual void Tick(double DeltaTime) override { std::cout << "Sprite tick" << std::endl; }


	void SetSprite(std::shared_ptr<Sprite> _sprite) { sprite = _sprite; }
	std::shared_ptr<Sprite> GetSpriteComponent() const { return sprite; }
private:
	std::shared_ptr<Sprite> sprite;
};