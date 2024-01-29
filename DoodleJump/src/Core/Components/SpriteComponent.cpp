#include "SpriteComponent.h"
#include "World/World.h"
#include "World/Scene.h"
#include <algorithm>

SpriteComponent::~SpriteComponent()
{

}

void SpriteComponent::Tick(double deltaTime)
{
	if (!bAnimationEnabled)
		return;
	if (currentTime < frameTime)
	{
		sprite = (*animationState)[index];
		currentTime += deltaTime;
		return;
	}

	currentTime -= frameTime;
	index++;
	index = std::clamp(index, (size_t)0, (size_t)animationState->size()-1);
	sprite = (*animationState)[index];
	currentTime += deltaTime;

}

void SpriteComponent::Destroy()
{
	GetScene()->DestroyDrawObject(GetScene()->GetComponent(this));
}

void SpriteComponent::SetSprite(std::shared_ptr<MySprite> newSprite)
{
	sprite = newSprite;
}

std::shared_ptr<MySprite> SpriteComponent::GetSprite() const
{
	return sprite; 
}

void SpriteComponent::EnableAnimation()
{
	bAnimationEnabled = true;
}

void SpriteComponent::SetAnimationMachine(std::shared_ptr<AnimationMachine> anim)
{
	animations = anim;
}

void SpriteComponent::SwitchAnimationState(const std::string& key)
{
	auto [animState, ft] = animations->at(key);
	frameTime = ft;
	animationState = animState;
	currentTime = 0;
	index = 0;
}
