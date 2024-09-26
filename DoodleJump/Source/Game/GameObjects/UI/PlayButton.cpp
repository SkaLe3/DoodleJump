#include "PlayButton.h"
#include "Components/SpriteComponent.h"
#include "Core/Base/Log.h"

PlayButton::PlayButton()
{
	m_SpriteComponent = CreateComponent<SpriteComponent>();
	m_SpriteComponent->SetupAttachment(GetBoxComponent());

	std::shared_ptr<MySprite> spriteRef = std::make_shared<MySprite>("assets2/play.png");
	m_SpriteComponent->SetSprite(spriteRef);

	m_BoxComponent->SetHalfSize({ 5.8, 2 });
	m_BoxComponent->GetTransform().Translation = { -6, 3, 0 };
	OBJECT_LOG_CONSTRUCTOR()
}

PlayButton::~PlayButton()
{
	OBJECT_LOG_DESTRUCTOR()
}

void PlayButton::Start()
{
	GameObject::Start();
	auto button = GetScene()->GetObject(this);
	m_SpriteComponent->SetOwner(button);
	m_SpriteComponent->GetTransform().Scale = { 12, 4.32, 1.0 };
	m_BoxComponent->SetCollisionEnabled(false);
}

void PlayButton::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);
}

void PlayButton::Destroy()
{
	GameObject::Destroy();
	m_SpriteComponent->Destroy();
}

