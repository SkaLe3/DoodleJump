#pragma once
#include "Framework.h"

#include "SceneComponent.h"


class SpriteComponent : SceneComponent
{
public:
	SpriteComponent() : sprite(nullptr) {}
	SpriteComponent(Sprite* _sprite) : sprite(_sprite) {}

	virtual void Tick() override {}


	void SetSprite(Sprite* _sprite) { sprite = _sprite; }
	Sprite* GetSprite() const { return sprite; }
private:
	Sprite* sprite;
};