#include "Projectile.h"
#include "Core/Base/Log.h"
#include "Core/Base/AssetManager.h"
#include "Core/Components/SpriteComponent.h"
#include "Core/World/World.h"

#include "Components/ProjectileMovementComponent.h"
#include "GameModes/DJGameMode.h"

Projectile::Projectile() : GameObject()
{
	m_SpriteComponent = CreateComponent<SpriteComponent>();
	m_SpriteComponent->SetupAttachment(GetBoxComponent());
	m_MovementComponent = CreateComponent<ProjectileMovementComponent>();

	m_SpriteComponent->SetSprite(AssetManager::Get().GetAsset<MySprite>("S_Cocos"));
	m_BoxComponent->SetHalfSize({ 1, 1 });

	OBJECT_LOG_CONSTRUCTOR()
}
Projectile::~Projectile()
{
	OBJECT_LOG_DESTRUCTOR()
}

void Projectile::Start()
{
	GameObject::Start();

	auto projectile = GetScene()->GetObject(this);
	m_SpriteComponent->SetOwner(projectile);
	m_MovementComponent->SetOwner(projectile);

	m_BoxComponent->OnBeginOverlap.Add(std::bind(&Projectile::OnCollision, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	m_BoxComponent->SetCollisionChannel(ECollisionChannel::WorldDynamic);
	m_BoxComponent->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Ignore);
	m_BoxComponent->SetCollisionResponce(ECollisionChannel::Character, ECollisionResponse::Ignore);

	m_SpriteComponent->GetTransform().Scale = { 1, 1 , 1.0 };
	m_SpriteComponent->GetTransform().Translation = { 0.0, 0.0, 0.0 };

	m_MovementComponent->SetGravity(0); 
	m_MovementComponent->SetMaxSpeed(50);
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
	m_MovementComponent->Destroy();
	m_SpriteComponent->Destroy();
}



void Projectile::OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime)
{
	std::string otherTag = otherObject->GetTag();
	std::shared_ptr<DJGameMode> gameMode = static_pointer_cast<DJGameMode>(GetGameMode());

	if (otherTag == "left wall")
	{
		gameMode->TeleportToRightWall(GetScene()->GetObject(this));
	}
	if (otherTag == "right wall")
	{
		gameMode->TeleportToLeftWall(GetScene()->GetObject(this));
	}

	if (otherTag == "monster")
	{
		otherObject->Destroy();
		Destroy();
	}
}

void Projectile::Launch(Math::Vector2D direction, double speed)
{
	m_MovementComponent->SetInitialVelocity(Math::Normalize(direction) * speed);
}
