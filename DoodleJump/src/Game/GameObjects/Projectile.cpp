#include "Projectile.h"

Projectile::Projectile() : GameObject()
{
	spriteComponent = CreateComponent<SpriteComponent>();
	spriteComponent->SetupAttachment(GetBoxComponent());

	movementComponent = CreateComponent<MovementComponent>();

	Sprite* sprite = createSprite("assets/bubble@2x.png");
	std::shared_ptr<Sprite> spriteRef;
	spriteRef.reset(sprite);
	spriteComponent->SetSprite(spriteRef);

	boxComponent->SetHalfSize({ 1, 1 });
}

void Projectile::Start()
{
	GameObject::Start();

	auto projectile = GetScene()->GetObject(this);
	spriteComponent->SetOwner(projectile);
	movementComponent->SetOwner(projectile);

	//boxComponent->OnBeginOverlap.Add(std::bind(&Doodle::OnCollision, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));


	spriteComponent->GetTransform().Scale = { 1, 1 , 1.0 };
	spriteComponent->GetTransform().Translation = { 0.0, 0.0, 0.0 };

	boxComponent->SetCollisionChannel(ECollisionChannel::WorldDynamic);
	boxComponent->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Ignore);
	boxComponent->SetCollisionResponce(ECollisionChannel::Character, ECollisionResponse::Ignore);



	movementComponent->SetGravity(0); 
	movementComponent->SetMaxSpeed(50);
}

void Projectile::Tick(double DeltaTime)
{
	GameObject::Tick(DeltaTime);
}
