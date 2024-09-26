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
	m_AnimationMachine->Update(deltaTime);
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
	if (!bAnimationEnabled)
		return sprite;
	else
		return m_AnimationMachine->GetActiveFrame();
}

void SpriteComponent::EnableAnimation()
{
	bAnimationEnabled = true;
}

void SpriteComponent::SetAnimationMachine(std::shared_ptr<AnimationMachine> anim)
{
	m_AnimationMachine = anim;
}

void SpriteComponent::SwitchAnimationState(const std::string& key)
{
	 m_AnimationMachine->SwitchState(key);
}


