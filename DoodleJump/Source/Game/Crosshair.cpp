#include "Crosshair.h"
#include "Input/EventHandler.h"
#include "Math/Vector2D.h"
#include "Framework.h"
#include "Core/Base/Log.h"

Crosshair::Crosshair()
{
	m_SpriteComponent = CreateComponent<SpriteComponent>();
	m_SpriteComponent->SetupAttachment(GetBoxComponent());

	std::shared_ptr<MySprite> spriteRef = std::make_shared<MySprite>("assets2/crosshair.png");
	m_SpriteComponent->SetSprite(spriteRef);
	OBJECT_LOG_CONSTRUCTOR()
}

Crosshair::~Crosshair()
{
	OBJECT_LOG_DESTRUCTOR()
}

void Crosshair::Start()
{
	GameObject::Start();

	auto crosshair = GetScene()->GetObject(this);
	m_SpriteComponent->SetOwner(crosshair);

	m_SpriteComponent->GetTransform().Scale = { 2, 2, 1.0 };
	m_SpriteComponent->GetTransform().Translation = { 0, 0, 10 };
	
	m_BoxComponent->SetCollisionEnabled(false);
}

void Crosshair::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);

	Math::Vector2D mousePos = GetScene()->GetMousePosition();
	m_RootComponent->GetTransform().Translation = Math::Vector(mousePos, 0);
}

void Crosshair::Destroy()
{
	GameObject::Destroy();
	m_SpriteComponent->Destroy();	
}
