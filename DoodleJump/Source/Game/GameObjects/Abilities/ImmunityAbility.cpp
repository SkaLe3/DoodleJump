#include "ImmunityAbility.h"


#include "Components/SpriteComponent.h"

ImmunityAbility::ImmunityAbility() : GameObject()
{
	spriteComponent = CreateComponent<SpriteComponent>();
	spriteComponent->SetupAttachment(GetBoxComponent());

	boxComponent->SetHalfSize({3, 3 });
	std::shared_ptr<MySprite> spriteRef = std::make_shared<MySprite>("assets2/shield.png");
	spriteComponent->SetSprite(spriteRef);
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
	spriteComponent->SetOwner(ability);

	spriteComponent->GetTransform().Scale = { 7, 7, 1.0 };

	boxComponent->SetCollisionChannel(ECollisionChannel::WorldStatic);
	boxComponent->SetCollisionResponce(ECollisionChannel::Character, ECollisionResponse::Overlap);
	boxComponent->SetCollisionResponce(ECollisionChannel::WorldStatic, ECollisionResponse::Ignore);
	boxComponent->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Ignore);

	SetTag("immunity");
}

void ImmunityAbility::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);
}

void ImmunityAbility::Destroy()
{
	GameObject::Destroy();
	spriteComponent->Destroy();
}

void ImmunityAbility::DisableCollision()
{
	boxComponent->SetCollisionEnabled(false);
}

double ImmunityAbility::GetTime()
{
	return abilityTime;
}

