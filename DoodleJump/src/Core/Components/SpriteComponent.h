#pragma once
#include "SceneComponent.h"
#include "Renderer/MySprite.h"
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
	~SpriteComponent();

	virtual void Start() override {}
	virtual void Tick(double DeltaTime) override {  }
	virtual void Destroy() override;


	void SetSprite(std::shared_ptr<MySprite> _sprite) { sprite = _sprite; }
	std::shared_ptr<MySprite> GetSpriteComponent() const { return sprite; }
private:
	std::shared_ptr<MySprite> sprite;
	std::unordered_map<EAnimationState,std::shared_ptr<MySprite>> spriteMap;
};