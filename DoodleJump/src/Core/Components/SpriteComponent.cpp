#include "SpriteComponent.h"
#include "World/World.h"
#include "World/Scene.h"
#include <algorithm>

SpriteComponent::~SpriteComponent()
{

}

void SpriteComponent::Tick(double DeltaTime)
{
	if (!bAnimationEnabled)
		return;
	if (currentTime < frameTime)
	{
		sprite = (*animationState)[index];
		currentTime += DeltaTime;
		return;
	}

	currentTime -= frameTime;
	index++;
	index = std::clamp(index, (size_t)0, (size_t)animationState->size()-1);
	sprite = (*animationState)[index];
	currentTime += DeltaTime;

}

void SpriteComponent::Destroy()
{
	GetScene()->DestroyDrawObject(GetScene()->GetComponent(this));
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
