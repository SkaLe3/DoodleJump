#include "FakePlatform.h"
#include "Core/Base/AssetManager.h"
#include "Animations/FakePlatformAnimator.h"

FakePlatform::FakePlatform() : Platform()
{
	m_SpriteComponent->GetTransform().Scale = { 6, 2.95, 1 };
	m_SpriteComponent->GetTransform().Translation.z = -0.5;
	m_SpriteComponent->GetTransform().Translation.y = -0.3;
	m_BoxComponent->SetHalfSize({ 2.7, 0.5 });


	GetSprite()->SetAnimator(std::make_shared<FakePlatformAnimator>(this));
	GetSprite()->EnableAnimation();
}

void FakePlatform::Start()
{
	Platform::Start();

	m_BoxComponent->OnBeginOverlap.Add(std::bind(&FakePlatform::OnCollision, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void FakePlatform::Tick(double deltaTime)
{
	Platform::Tick(deltaTime);
	if (!m_bBroken)
		return;
	if (m_Timer >= 0.32)
	{
		m_bBroken = false;
		m_BoxComponent->GetTransform().Translation.y = -10;
		m_Timer = 0;
	}
	m_Timer += deltaTime;
}


void FakePlatform::OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime)
{
	std::string otherTag = otherObject->GetTag();
	if (normal.y < 0 && otherTag == "doodle")
	{
		Break();
	}
}

void FakePlatform::Break()
{
	m_bBroken = true;
}
