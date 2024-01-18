#include "Background.h"
#include <iostream>

Background::Background() : GameObject()
{
	spriteComponent = CreateComponent<SpriteComponent>();
	spriteComponent->SetupAttachment(GetBoxComponent());

	Sprite* sprite = createSprite("assets/bck@2x.png");
	std::shared_ptr<Sprite> bgSpriteRef;
	bgSpriteRef.reset(sprite);
	spriteComponent->SetSprite(bgSpriteRef);
}

void Background::Start()
{
	GameObject::Start();
	auto background = GetScene()->GetObject(this);
	spriteComponent->SetOwner(background);
	boxComponent->SetupAttachment(GetScene()->GetRenderCamera());
	boxComponent->SetCollisionEnabled(false);

	spriteComponent->GetTransform().Scale = { 45, 72, 1 };
	spriteComponent->GetTransform().Translation = { 4.5, 0, -1 };
}

void Background::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);


}
