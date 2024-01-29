#include "Crosshair.h"
#include "Input/EventHandler.h"
#include "Math/Vector2D.h"
#include "Framework.h"

Crosshair::Crosshair()
{
	spriteComponent = CreateComponent<SpriteComponent>();
	spriteComponent->SetupAttachment(GetBoxComponent());

	std::shared_ptr<MySprite> spriteRef = std::make_shared<MySprite>("assets/crosshair.png");
	spriteComponent->SetSprite(spriteRef);

}

void Crosshair::Start()
{
	GameObject::Start();

	auto crosshair = GetScene()->GetObject(this);
	spriteComponent->SetOwner(crosshair);

	spriteComponent->GetTransform().Scale = { 2, 2, 1.0 };
	spriteComponent->GetTransform().Translation = { 0, 0, 10 };
	
	boxComponent->SetCollisionEnabled(false);
}

void Crosshair::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);

	Math::Vector2D mousePos = GetScene()->GetMousePosition();

	rootComponent->GetTransform().Translation = Math::Vector(mousePos, 0);
}

void Crosshair::Destroy()
{
	GameObject::Destroy();
	spriteComponent->Destroy();
}
