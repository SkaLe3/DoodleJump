#include "Platform.h"
#include "Core/Base/Log.h"
#include "Core/Base/AssetManager.h"

Platform::Platform() : GameObject()
{
	m_SpriteComponent = CreateComponent<SpriteComponent>();
	m_SpriteComponent->SetupAttachment(GetBoxComponent());

	m_SpriteComponent->GetTransform().Scale = { 6, 1.565, 1 };
	m_SpriteComponent->GetTransform().Translation.z = -0.5;
	m_SpriteComponent->SetSprite(AssetManager::Get().GetAsset<MySprite>("S_Platform"));
	m_BoxComponent->SetHalfSize({ 2.7, 0.5 });
	m_BoxComponent->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Ignore);
	OBJECT_LOG_CONSTRUCTOR()
}

Platform::~Platform()
{
	OBJECT_LOG_DESTRUCTOR()
}

void Platform::Start()
{
	GameObject::Start();
	auto platform = GetScene()->GetObject(this);
	m_SpriteComponent->SetOwner(platform);
}

void Platform::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);
}

void Platform::Destroy()
{
	GameObject::Destroy();
	m_SpriteComponent->Destroy();
}

void Platform::Pass()
{
	m_bPassed = true;
}

bool Platform::IsPassed()
{
	return m_bPassed;
}

void Platform::Reset()
{
	m_bPassed = false;
}
