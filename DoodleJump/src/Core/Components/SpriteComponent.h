#pragma once
#include "SceneComponent.h"
#include "Renderer/MySprite.h"
#include <unordered_map>
#include <string>
#include <vector>
// TESTING
#include <iostream>

using AnimationMachine = std::unordered_map<std::string, std::pair<std::shared_ptr<std::vector<std::shared_ptr<MySprite>>>, double>>;

class SpriteComponent : public SceneComponent
{
public:
	SpriteComponent() = default;
	~SpriteComponent();

	virtual void Start() override {}
	virtual void Tick(double DeltaTime) override;
	virtual void Destroy() override;


	void SetSprite(std::shared_ptr<MySprite> _sprite) { sprite = _sprite; }
	std::shared_ptr<MySprite> GetSpriteComponent() const { return sprite; }
	
	void EnableAnimation();
	void SetAnimationMachine(std::shared_ptr<AnimationMachine> anim);
	void SwitchAnimationState(const std::string& key);
private:
	std::shared_ptr<MySprite> sprite;
	std::shared_ptr<AnimationMachine> animations;
	std::shared_ptr<std::vector<std::shared_ptr<MySprite>>> animationState;
	size_t index = 0;
	double frameTime = 1;

	double currentTime = 0;

	bool bAnimationEnabled = false;

};