#include "Platform.h"
#include "Core/Base/Log.h"
Platform::Platform() : GameObject()
{
	spriteComponent = CreateComponent<SpriteComponent>();
	spriteComponent->SetupAttachment(GetBoxComponent());

	spriteComponent->GetTransform().Scale = { 6, 1.565, 1 };
	spriteComponent->GetTransform().Translation.z = -0.5;
	boxComponent->SetHalfSize({ 2.7, 0.5 });
	boxComponent->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Ignore);
	OBJECT_LOG_CONSTRUCTOR()
}

Platform::~Platform()
{
	OBJECT_LOG_DESTRUCTOR()
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

void Platform::Destroy()
{
	GameObject::Destroy();
	spriteComponent->Destroy();
}

void Platform::Pass()
{
	bPassed = true;
}

bool Platform::IsPassed()
{
	return bPassed;
}

void Platform::Reset()
{
	bPassed = false;
}
