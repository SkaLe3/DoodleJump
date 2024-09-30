#include "Monster.h"
#include "GameModes/DJGameMode.h"
#include "Doodle.h"
#include "Core/Base/Log.h"
#include "Core/Base/AssetManager.h"

#include <string>

Monster::Monster()
{
	m_SpriteComponent = CreateComponent<SpriteComponent>();
	m_SpriteComponent->SetupAttachment(GetBoxComponent());
	m_SpriteComponent->SetSprite(AssetManager::Get().GetAsset<MySprite>("S_UnderwaterMonster"));

	m_BoxComponent->SetHalfSize({ 3, 2.73 });
	OBJECT_LOG_CONSTRUCTOR()
}

Monster::~Monster()
{
	OBJECT_LOG_DESTRUCTOR()
}

void Monster::Start()
{
	GameObject::Start();
	auto monster = GetScene()->GetObject(this);
	m_SpriteComponent->SetOwner(monster);

	m_SpriteComponent->GetTransform().Scale = { 8, 5.455, 1.0 };
	m_SpriteComponent->GetTransform().Translation = { 0.0, 0.0, 0.0 };

	m_BoxComponent->SetCollisionChannel(ECollisionChannel::WorldStatic);
	m_BoxComponent->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Overlap);
	m_BoxComponent->SetCollisionResponce(ECollisionChannel::WorldStatic, ECollisionResponse::Ignore);

	m_BoxComponent->OnBeginOverlap.Add(std::bind(&Monster::OnCollision, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	SetTag("monster");
}

void Monster::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);
}

void Monster::Destroy()
{
	GameObject::Destroy();
	m_SpriteComponent->Destroy();
}

void Monster::OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime)
{
	std::string tag = otherObject->GetTag();
	if (tag == "doodle" && normal.y >= 0 && !static_pointer_cast<Doodle>(otherObject)->HasImmunity())
	{
		std::shared_ptr<DJGameMode> gameMode = static_pointer_cast<DJGameMode>(GetGameMode());
		gameMode->KillDoodle();
	}
}
