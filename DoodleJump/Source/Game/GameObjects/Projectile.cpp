#include "Projectile.h"
#include "Core/Base/Log.h"
#include "Core/Base/AssetManager.h"
#include "Core/Components/SpriteComponent.h"
#include "Core/World/World.h"

#include "Components/ProjectileMovementComponent.h"
#include "GameModes/DJGameMode.h"
#include "GameObjects/Monster.h"

Projectile::Projectile() : GameObject()
{
	m_SpriteComponent = CreateComponent<SpriteComponent>();
	auto sprite = GetSpriteComponent();
	sprite->SetupAttachment(GetBoxComponent());
	sprite->SetSprite(AssetManager::Get().GetAsset<MySprite>("S_Cocos"));

	m_MovementComponent = CreateComponent<ProjectileMovementComponent>();
	GetBoxComponent()->SetHalfSize({ 1, 1 });

	OBJECT_LOG_CONSTRUCTOR()
}
Projectile::~Projectile()
{
	OBJECT_LOG_DESTRUCTOR()
}

void Projectile::Start()
{
	GameObject::Start();
	auto sprite = GetSpriteComponent();
	auto movement = GetMovementComponent();
	auto box = GetBoxComponent();

	sprite->SetOwner(GetSelf());
	movement->SetOwner(GetSelf());

	box->OnBeginOverlap.Add(std::bind(&Projectile::OnCollision, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	box->SetCollisionChannel(ECollisionChannel::WorldDynamic);
	box->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Ignore);
	box->SetCollisionResponce(ECollisionChannel::Character, ECollisionResponse::Ignore);

	sprite->GetTransform().Scale = { 8, 8 , 1.0 };
	sprite->GetTransform().Translation = { 0.0, 0.0, 0.0 };

	movement->SetGravity(0);
	movement->SetMaxSpeed(50);
}

void Projectile::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);
	m_AutoDestroyTimer += deltaTime;

	if (m_AutoDestroyTimer > 2)
		Destroy();
}

void Projectile::Destroy()
{
	GameObject::Destroy();
	GetMovementComponent()->Destroy();
	GetSpriteComponent()->Destroy();
}



void Projectile::OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime)
{
	std::string otherTag = otherObject->GetTag();
	std::shared_ptr<DJGameMode> gameMode = static_pointer_cast<DJGameMode>(GetGameMode());

	if (otherTag == "left wall")
	{
		gameMode->TeleportToRightWall(GetSelf());
	}
	if (otherTag == "right wall")
	{
		gameMode->TeleportToLeftWall(GetSelf());
	}

	if (otherTag == "monster")
	{
		std::static_pointer_cast<Monster>(otherObject)->Kill();
		Destroy();
	}
}

void Projectile::Launch(Math::Vector2D direction, double speed)
{
	GetMovementComponent()->SetInitialVelocity(Math::Normalize(direction) * speed);
}
