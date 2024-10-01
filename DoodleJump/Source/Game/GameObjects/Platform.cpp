#include "Platform.h"
#include "Core/Base/Log.h"
#include "Core/Base/AssetManager.h"

Platform::Platform() : GameObject()
{
	m_SpriteComponent = CreateComponent<SpriteComponent>();
	auto sprite = GetSpriteComponent();
	sprite->SetupAttachment(GetBoxComponent());

	sprite->GetTransform().Scale = { 6, 1.565, 1 };
	sprite->GetTransform().Translation.z = -0.5;
	sprite->SetSprite(AssetManager::Get().GetAsset<MySprite>("S_Bamboo"));
	auto box = GetBoxComponent();
	box->SetHalfSize({ 2.7, 0.5 });
	box->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Ignore);
	OBJECT_LOG_CONSTRUCTOR()
}

Platform::~Platform()
{
	OBJECT_LOG_DESTRUCTOR()
}

void Platform::Start()
{
	GameObject::Start();
	GetSpriteComponent()->SetOwner(GetSelf());
}

void Platform::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);
}

void Platform::Destroy()
{
	GameObject::Destroy();
	GetSpriteComponent()->Destroy();
}

void Platform::Pass()
{
	m_bPassed = true;
}

bool Platform::IsPassed()
{
	return m_bPassed;
}

void Platform::Reset()
{
	m_bPassed = false;
}
