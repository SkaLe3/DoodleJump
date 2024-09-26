#include "SpriteComponent.h"
#include "World/World.h"
#include "World/Scene.h"
#include <algorithm>


SpriteComponent::~SpriteComponent()
{

}

void SpriteComponent::Tick(double deltaTime)
{
	if (!m_bAnimationEnabled)
		return;
	m_AnimationMachine->Update(deltaTime);
}

void SpriteComponent::Destroy()
{
	GetScene()->DestroyDrawObject(GetScene()->GetComponent(this));
}

void SpriteComponent::SetSprite(std::shared_ptr<MySprite> newSprite)
{
	m_Sprite = newSprite;
}

std::shared_ptr<MySprite> SpriteComponent::GetSprite() const
{
	if (!m_bAnimationEnabled)
		return m_Sprite;
	else
		return m_AnimationMachine->GetActiveFrame();
}

void SpriteComponent::EnableAnimation()
{
	m_bAnimationEnabled = true;
}

void SpriteComponent::SetAnimationMachine(std::shared_ptr<AnimationMachine> anim)
{
	m_AnimationMachine = anim;
}

void SpriteComponent::SwitchAnimationState(const std::string& key)
{
	 m_AnimationMachine->SwitchState(key);
}


