#include "Background.h"
#include <iostream>

Background::Background() : GameObject()
{
	spriteComponent = CreateComponent<SpriteComponent>();
	spriteComponent->SetupAttachment(GetBoxComponent());

	std::shared_ptr<MySprite> spriteRef = std::make_shared<MySprite>("assets/hop-bck@2x.png");
	spriteComponent->SetSprite(spriteRef);
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

void Background::Destroy()
{
	GameObject::Destroy();
	spriteComponent->Destroy();
}
