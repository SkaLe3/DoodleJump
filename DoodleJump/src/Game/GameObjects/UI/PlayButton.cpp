#include "PlayButton.h"
#include "Components/SpriteComponent.h"

PlayButton::PlayButton()
{
	spriteComponent = CreateComponent<SpriteComponent>();
	spriteComponent->SetupAttachment(GetBoxComponent());

	std::shared_ptr<MySprite> spriteRef = std::make_shared<MySprite>("assets/play.png");
	spriteComponent->SetSprite(spriteRef);

	boxComponent->SetHalfSize({ 5.8, 2 });
	boxComponent->GetTransform().Translation = { -6, 3, 0 };
}

void PlayButton::Start()
{
	GameObject::Start();
	auto buttron = GetScene()->GetObject(this);
	spriteComponent->SetOwner(buttron);

	spriteComponent->GetTransform().Scale = { 12, 4.32, 1.0 };


	boxComponent->SetCollisionEnabled(false);

	
}

void PlayButton::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);
}

void PlayButton::Destroy()
{
	GameObject::Destroy();
	spriteComponent->Destroy();
}

