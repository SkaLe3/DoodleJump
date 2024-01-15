#pragma once
#include "Framework.h"

#include "SceneComponent.h"

// TESTING
#include <iostream>
class SpriteComponent : public SceneComponent
{
public:
	SpriteComponent() : sprite(nullptr) {}
	SpriteComponent(Sprite* _sprite) : sprite(_sprite) {}

	virtual void Start() override {}
	virtual void Tick(double DeltaTime) override { std::cout << "Sprite tick" << std::endl; }


	void SetSprite(Sprite* _sprite) { sprite = _sprite; }
	Sprite* GetSprite() const { return sprite; }
private:
	Sprite* sprite;
};