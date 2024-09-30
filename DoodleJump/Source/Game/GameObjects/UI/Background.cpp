#include "Background.h"
#include "Components/CameraComponent.h"	  
#include "Core/Base/Log.h"

Background::Background() : GameObject()
{
	m_SpriteComponent = CreateComponent<SpriteComponent>();
	m_SpriteComponent->SetupAttachment(GetBoxComponent());

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
	m_SpriteComponent->SetOwner(background);
	m_BoxComponent->SetupAttachment(GetScene()->GetRenderCamera());
	m_BoxComponent->SetCollisionEnabled(false);

}

void Background::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);


}

void Background::Destroy()
{
	GameObject::Destroy();
	m_SpriteComponent->Destroy();
}
