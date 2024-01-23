#include "Background.h"
#include "Components/CameraComponent.h"

Background::Background() : GameObject()
{
	spriteComponent = CreateComponent<SpriteComponent>();
	spriteComponent->SetupAttachment(GetBoxComponent());

	std::shared_ptr<MySprite> spriteRef = std::make_shared<MySprite>("assets/background.png");
	spriteComponent->SetSprite(spriteRef);
	spriteComponent->GetTransform().Scale = { 134.44, 72, 1 };
	spriteComponent->GetTransform().Translation = { 4.5, 0, -1 };
}

void Background::Start()
{
	GameObject::Start();
	auto background = GetScene()->GetObject(this);
	spriteComponent->SetOwner(background);
	boxComponent->SetupAttachment(GetScene()->GetRenderCamera());
	boxComponent->SetCollisionEnabled(false);

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
