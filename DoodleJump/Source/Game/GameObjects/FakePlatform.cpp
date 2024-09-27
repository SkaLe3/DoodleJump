#include "FakePlatform.h"
#include "Core/Base/AssetManager.h"
#include <memory>

FakePlatform::FakePlatform() : Platform()
{
	m_SpriteComponent->GetTransform().Scale = { 6, 2.95, 1 };
	m_SpriteComponent->GetTransform().Translation.z = -0.5;
	m_SpriteComponent->GetTransform().Translation.y = -0.3;
	m_BoxComponent->SetHalfSize({ 2.7, 0.5 });

	// Asset Manager should be implemented to avoid multiple loading of the same images
	std::shared_ptr<MySprite> fpFrame1 = AssetManager::Get().GetAsset<MySprite>("S_FakePlatform1");
	std::shared_ptr<MySprite> fpFrame2 = AssetManager::Get().GetAsset<MySprite>("S_FakePlatform2");
	std::shared_ptr<MySprite> fpFrame3 = AssetManager::Get().GetAsset<MySprite>("S_FakePlatform3");
	std::shared_ptr<MySprite> fpFrame4 = AssetManager::Get().GetAsset<MySprite>("S_FakePlatform4");

	std::shared_ptr<AnimationMachine> animMachine = AnimationMachine::Create();
	animMachine->CreateState("break", 0.08);
	animMachine->CreateState("idle", -1);
	animMachine->AddFrame("break", fpFrame1);
	animMachine->AddFrame("break", fpFrame2);
	animMachine->AddFrame("break", fpFrame3);
	animMachine->AddFrame("break", fpFrame4);
	animMachine->AddFrame("idle", fpFrame1);
	animMachine->SetEntryState("idle");
	GetSprite()->SetAnimationMachine(animMachine);
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
	if (m_Timer >= GetSprite()->GetActiveAnimationDuration())
	{
		m_bBroken = false;
		m_BoxComponent->GetTransform().Translation.y = -10;
		m_SpriteComponent->SwitchAnimationState("idle");
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
	m_SpriteComponent->SwitchAnimationState("break");
	m_bBroken = true;
}
