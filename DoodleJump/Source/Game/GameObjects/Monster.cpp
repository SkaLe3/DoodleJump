#include "Monster.h"
#include "Core/Base/Log.h"
#include "Core/Base/AssetManager.h"
#include "GameModes/DJGameMode.h"
#include "GameObjects/DoodleController.h"

#include <string>

Monster::Monster()
{
	m_SpriteComponent = CreateComponent<SpriteComponent>();
	auto sprite = GetSpriteComponent();
	sprite->SetupAttachment(GetBoxComponent());
	sprite->SetSprite(AssetManager::Get().GetAsset<MySprite>("S_UnderwaterMonster"));

	auto box = GetBoxComponent();
	box->SetHalfSize({ 2.9, 2.5 });
	OBJECT_LOG_CONSTRUCTOR()
}

Monster::~Monster()
{
	OBJECT_LOG_DESTRUCTOR()
}

void Monster::Start()
{
	GameObject::Start();
	auto sprite = GetSpriteComponent();
	auto box = GetBoxComponent();
	sprite->SetOwner(GetSelf());

	sprite->GetTransform().Scale = { 13.3, 6.65, 1.0 };
	sprite->GetTransform().Translation = { 0.0, 0.0, 0.0 };


	box->SetCollisionChannel(ECollisionChannel::WorldStatic);
	box->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Overlap);
	box->SetCollisionResponce(ECollisionChannel::WorldStatic, ECollisionResponse::Ignore);

	box->OnBeginOverlap.Add(std::bind(&Monster::OnCollision, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	SetTag("monster");
}

void Monster::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);
}

void Monster::Destroy()
{
	GameObject::Destroy();
	GetSpriteComponent()->Destroy();
}

void Monster::OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime)
{
	std::string tag = otherObject->GetTag();
	if (tag == "doodle" && normal.y >= 0 && !static_pointer_cast<DoodleController>(otherObject)->GetImmunity())
	{
		std::shared_ptr<DJGameMode> gameMode = static_pointer_cast<DJGameMode>(GetGameMode());
		gameMode->KillDoodle();
	}
}
