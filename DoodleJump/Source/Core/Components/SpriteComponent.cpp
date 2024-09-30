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
	m_Animator->Update(deltaTime);
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
		return m_Animator->GetFrame();
}

void SpriteComponent::EnableAnimation()
{
	m_bAnimationEnabled = true;
}

void SpriteComponent::SetAnimator(std::shared_ptr<Animator> animator)
{
	m_Animator = animator;
}


