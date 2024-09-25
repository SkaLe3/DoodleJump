#include "Background.h"
#include "Components/CameraComponent.h"	  
#include "Core/Base/Log.h"

Background::Background() : GameObject()
{
	spriteComponent = CreateComponent<SpriteComponent>();
	spriteComponent->SetupAttachment(GetBoxComponent());

	OBJECT_LOG_CONSTRUCTOR()
}

Background::~Background()
{
	OBJECT_LOG_DESTRUCTOR()
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
