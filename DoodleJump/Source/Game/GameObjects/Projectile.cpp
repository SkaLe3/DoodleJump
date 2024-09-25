#include "Projectile.h"
#include "Components/ProjectileMovementComponent.h"
#include "Components/SpriteComponent.h"
#include "World/World.h"
#include "GameModes/DJGameMode.h"
#include "Math/MyMath.h"

#include "Core/Base/Log.h"
Projectile::Projectile() : GameObject()
{
	spriteComponent = CreateComponent<SpriteComponent>();
	spriteComponent->SetupAttachment(GetBoxComponent());

	movementComponent = CreateComponent<ProjectileMovementComponent>();

	std::shared_ptr<MySprite> spriteRef = std::make_shared<MySprite>("assets2/bubble@2x.png");

	std::shared_ptr<MySprite> spriteRef2 = std::make_shared<MySprite>("assets2/bubble@2x.png");
	spriteRef2 = nullptr;
	spriteComponent->SetSprite(spriteRef);

	boxComponent->SetHalfSize({ 1, 1 });

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
	spriteComponent->SetOwner(projectile);
	movementComponent->SetOwner(projectile);

	boxComponent->OnBeginOverlap.Add(std::bind(&Projectile::OnCollision, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	boxComponent->SetCollisionChannel(ECollisionChannel::WorldDynamic);
	boxComponent->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Ignore);
	boxComponent->SetCollisionResponce(ECollisionChannel::Character, ECollisionResponse::Ignore);

	spriteComponent->GetTransform().Scale = { 1, 1 , 1.0 };
	spriteComponent->GetTransform().Translation = { 0.0, 0.0, 0.0 };

	movementComponent->SetGravity(0); 
	movementComponent->SetMaxSpeed(50);
}

void Projectile::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);
	autoDestroyTimer += deltaTime;

	if (autoDestroyTimer > 2)
		Destroy();
}

void Projectile::Destroy()
{
	GameObject::Destroy();
	movementComponent->Destroy();
	spriteComponent->Destroy();
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
	movementComponent->SetInitialVelocity(Math::Normalize(direction) * speed);
}
