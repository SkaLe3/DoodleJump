#include "SpriteComponent.h"
#include "World/World.h"
#include "Renderer/MySprite.h"
#include "Renderer/Animator.h"


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
	GetScene()->DestroyDrawObject(GetSelf());
}

void SpriteComponent::SetSprite(std::shared_ptr<MySprite> newSprite)
{
	m_Sprite = newSprite;
}

std::shared_ptr<MySprite> SpriteComponent::GetSpriteComponent() const
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


