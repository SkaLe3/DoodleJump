#include "Crosshair.h"
#include "Framework.h"
#include "Core/Input/EventHandler.h"
#include "Core/Base/Log.h"
#include "Core/Base/AssetManager.h"

Crosshair::Crosshair()
{
	m_SpriteComponent = CreateComponent<SpriteComponent>();
	auto sprite = GetSpriteComponent();

	sprite->SetupAttachment(GetBoxComponent());
	sprite->SetSprite(AssetManager::Get().GetAsset<MySprite>("S_Crosshair"));
	OBJECT_LOG_CONSTRUCTOR()
}

Crosshair::~Crosshair()
{
	OBJECT_LOG_DESTRUCTOR()
}

void Crosshair::Start()
{
	GameObject::Start();
	auto sprite = GetSpriteComponent();
	auto box = GetBoxComponent();

	sprite->SetOwner(GetSelf());
	sprite->GetTransform().Scale = { 2, 2, 1.0 };
	sprite->GetTransform().Translation = { 0, 0, 10 };
	
	box->SetCollisionEnabled(false);
}

void Crosshair::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);

	Math::Vector2D mousePos = GetScene()->GetMousePosition();
	GetRoot()->GetTransform().Translation = Math::Vector(mousePos, 0);
}

void Crosshair::Destroy()
{
	GameObject::Destroy();
	GetSpriteComponent()->Destroy();	
}
