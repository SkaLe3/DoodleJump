#include "ImmunityAbility.h"
#include "Core/Components/SpriteComponent.h"
#include "Core/Base/AssetManager.h"
#include "Animations/ShieldAnimator.h"

ImmunityAbility::ImmunityAbility() : GameObject()
{
	m_SpriteComponent = CreateComponent<SpriteComponent>();
	auto sprite = GetSpriteComponent();
	sprite->SetupAttachment(GetBoxComponent());
	sprite->SetAnimator(std::make_shared<ShieldAnimator>(this));
	sprite->EnableAnimation();


	auto box = GetBoxComponent();
	box->SetHalfSize({ 2, 2 });
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
	sprite->GetTransform().Scale = { 10, 10, 1.0 };

	box->SetCollisionChannel(ECollisionChannel::WorldStatic);
	box->SetCollisionResponce(ECollisionChannel::Character, ECollisionResponse::Overlap);
	box->SetCollisionResponce(ECollisionChannel::WorldStatic, ECollisionResponse::Ignore);
	box->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Ignore);

	SetTag("immunity");
}

void ImmunityAbility::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);

	if (m_bActivated)
	{
		if (m_ImmunityTimer > m_AbilityTime)
		{
			Destroy();
		}
		else
		{
			m_ImmunityTimer += deltaTime;
		}
		if (m_ImmunityTimer > m_EndTime)
		{
			m_bEnding = true;
		}
	}
}

void ImmunityAbility::Destroy()
{
	GameObject::Destroy();
	GetSpriteComponent()->Destroy();
}

void ImmunityAbility::Activate()
{
	m_bActivated = true;
	DisableCollision();
}

void ImmunityAbility::DisableCollision()
{
	GetBoxComponent()->SetCollisionEnabled(false);
}

double ImmunityAbility::GetTime()
{
	return m_AbilityTime;
}

