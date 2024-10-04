#include "PlayButton.h"
#include "Core/Components/SpriteComponent.h"
#include "Core/Base/Log.h"
#include "Core/Base/AssetManager.h"

PlayButton::PlayButton()
{
	m_SpriteComponent = CreateComponent<SpriteComponent>();
	auto sprite = GetSpriteComponent();
	sprite->SetupAttachment(GetBoxComponent());
	sprite->SetSprite(AssetManager::Get().GetAsset<MySprite>("S_Play"));
	auto box = GetBoxComponent();
	box->SetHalfSize({ 5.8, 2 });
	OBJECT_LOG_CONSTRUCTOR()
}

PlayButton::~PlayButton()
{
	OBJECT_LOG_DESTRUCTOR()
}

void PlayButton::Start()
{
	GameObject::Start();
	auto sprite = GetSpriteComponent();
	sprite->SetOwner(GetSelf());
	sprite->GetTransform().Scale = { 13.6, 6.3, 1.0 };
	GetBoxComponent()->SetCollisionEnabled(false);
}

void PlayButton::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);
}

void PlayButton::Destroy()
{
	GameObject::Destroy();
	GetSpriteComponent()->Destroy();
}

