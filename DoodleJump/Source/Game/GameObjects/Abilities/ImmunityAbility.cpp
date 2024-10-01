#include "ImmunityAbility.h"
#include "Core/Components/SpriteComponent.h"
#include "Core/Base/AssetManager.h"

ImmunityAbility::ImmunityAbility() : GameObject()
{
	m_SpriteComponent = CreateComponent<SpriteComponent>();
	auto sprite = GetSpriteComponent();
	auto box = GetBoxComponent();
	sprite->SetupAttachment(GetBoxComponent());

	box->SetHalfSize({3, 3 });
	sprite->SetSprite(AssetManager::Get().GetAsset<MySprite>("S_Shield"));
	OBJECT_LOG_CONSTRUCTOR()
}

ImmunityAbility::~ImmunityAbility()
{
	OBJECT_LOG_DESTRUCTOR()
}

void ImmunityAbility::Start()
{
	GameObject::Start();
	auto sprite = GetSpriteComponent();
	auto box = GetBoxComponent();

	sprite->SetOwner(GetSelf());
	sprite->GetTransform().Scale = { 7, 7, 1.0 };

	box->SetCollisionChannel(ECollisionChannel::WorldStatic);
	box->SetCollisionResponce(ECollisionChannel::Character, ECollisionResponse::Overlap);
	box->SetCollisionResponce(ECollisionChannel::WorldStatic, ECollisionResponse::Ignore);
	box->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Ignore);

	SetTag("immunity");
}

void ImmunityAbility::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);
}

void ImmunityAbility::Destroy()
{
	GameObject::Destroy();
	GetSpriteComponent()->Destroy();
}

void ImmunityAbility::DisableCollision()
{
	GetBoxComponent()->SetCollisionEnabled(false);
}

double ImmunityAbility::GetTime()
{
	return m_AbilityTime;
}

