#pragma once
#include "Framework.h"

#include "SceneComponent.h"
#include <unordered_map>


enum class EAnimationState
{
	LeftIdle,
	LeftJump,
	RightIdle,
	RightJump,
	Shoot
};

// TESTING
#include <iostream>
class SpriteComponent : public SceneComponent
{
public:
	SpriteComponent() = default;

	virtual void Start() override {}
	virtual void Tick(double DeltaTime) override {  }
	virtual void Destroy() override;


	void SetSprite(std::shared_ptr<Sprite> _sprite) { sprite = _sprite; }
	std::shared_ptr<Sprite> GetSpriteComponent() const { return sprite; }
private:
	std::shared_ptr<Sprite> sprite;
	std::unordered_map<EAnimationState,std::shared_ptr<Sprite>> spriteMap;
};