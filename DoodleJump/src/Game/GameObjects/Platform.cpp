#include "Platform.h"

Platform::Platform() : GameObject()
{
	spriteComponent = CreateComponent<SpriteComponent>();
	spriteComponent->SetupAttachment(GetBoxComponent());

	// May be unsafe to use in c-tor
	spriteComponent->GetTransform().Scale = { 6, 1.62, 1 };
	boxComponent->SetHalfSize({ 2.7, 0.5 });
	boxComponent->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Ignore);

}

void Platform::Start()
{
	GameObject::Start();
	auto platform = GetScene()->GetObject(this);
	spriteComponent->SetOwner(platform);

}

void Platform::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);
}
