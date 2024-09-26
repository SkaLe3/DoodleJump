#include "ImmunityAbility.h"

#include "Components/SpriteComponent.h"

ImmunityAbility::ImmunityAbility() : GameObject()
{
	m_SpriteComponent = CreateComponent<SpriteComponent>();
	m_SpriteComponent->SetupAttachment(GetBoxComponent());

	m_BoxComponent->SetHalfSize({3, 3 });
	std::shared_ptr<MySprite> spriteRef = std::make_shared<MySprite>("assets2/shield.png");
	m_SpriteComponent->SetSprite(spriteRef);
	OBJECT_LOG_CONSTRUCTOR()
}

ImmunityAbility::~ImmunityAbility()
{
	OBJECT_LOG_DESTRUCTOR()
}

void ImmunityAbility::Start()
{
	GameObject::Start();
	auto ability = GetScene()->GetObject(this);
	m_SpriteComponent->SetOwner(ability);

	m_SpriteComponent->GetTransform().Scale = { 7, 7, 1.0 };

	m_BoxComponent->SetCollisionChannel(ECollisionChannel::WorldStatic);
	m_BoxComponent->SetCollisionResponce(ECollisionChannel::Character, ECollisionResponse::Overlap);
	m_BoxComponent->SetCollisionResponce(ECollisionChannel::WorldStatic, ECollisionResponse::Ignore);
	m_BoxComponent->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Ignore);

	SetTag("immunity");
}

void ImmunityAbility::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);
}

void ImmunityAbility::Destroy()
{
	GameObject::Destroy();
	m_SpriteComponent->Destroy();
}

void ImmunityAbility::DisableCollision()
{
	m_BoxComponent->SetCollisionEnabled(false);
}

double ImmunityAbility::GetTime()
{
	return m_AbilityTime;
}

