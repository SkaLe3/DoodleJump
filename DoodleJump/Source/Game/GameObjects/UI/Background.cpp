#include "Background.h"
#include "Core/Components/CameraComponent.h"	  
#include "Core/Base/Log.h"

Background::Background() : GameObject()
{
	m_SpriteComponent = CreateComponent<SpriteComponent>();
	auto sprite = GetSpriteComponent();
	sprite->SetupAttachment(GetBoxComponent());

	OBJECT_LOG_CONSTRUCTOR()
}

Background::~Background()
{
	OBJECT_LOG_DESTRUCTOR()
}

void Background::Start()
{
	GameObject::Start();
	auto sprite = GetSpriteComponent();
	auto box = GetBoxComponent();

	sprite->SetOwner(GetSelf());
	box->SetupAttachment(GetScene()->GetRenderCamera());
	box->SetCollisionEnabled(false);
}

void Background::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);
}

void Background::Destroy()
{
	GameObject::Destroy();
	GetSpriteComponent()->Destroy();
}
