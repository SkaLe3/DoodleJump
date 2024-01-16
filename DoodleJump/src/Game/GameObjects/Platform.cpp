#include "Platform.h"

Platform::Platform() : GameObject()
{
	spriteComponent = CreateComponent<SpriteComponent>();
	spriteComponent->SetupAttachment(GetBoxComponent());


}

void Platform::Start()
{
	GameObject::Start();
	auto platform = GetScene()->GetObject(this);
	spriteComponent->SetOwner(platform);

	spriteComponent->GetTransform().Scale = { 6, 1.62, 1 };
	boxComponent->SetHalfSize({ 3, 0.8 });
	boxComponent->GetTransform().Translation = { 0, 20, -0.5 };
	boxComponent->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Ignore);
}

void Platform::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);
}
