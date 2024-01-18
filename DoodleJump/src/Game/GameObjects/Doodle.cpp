#include "Doodle.h"
#include "Components/SpriteComponent.h"
#include "Math/Vector2D.h"
#include "Crosshair.h"
#include "Framework.h"

// TESTING
#include <iostream>
#include "World/World.h"
#include "Input/EventHandler.h"
#include "Input/TriggerEvent.h"
#include "Input/InputAction.h"
#include "Input/InputValue.h"
#include "Components/DoodleMovementComponent.h"
#include "Components/CameraComponent.h"
#include "Components/FollowCameraComponent.h"
#include <functional>
Doodle::Doodle() : GameObject()
{

	spriteComponent = CreateComponent<SpriteComponent>();
	spriteComponent->SetupAttachment(GetBoxComponent());

	// Don't need attachment
	cameraComponent = CreateComponent<FollowCameraComponent>();
	GetScene()->UseCamera(cameraComponent);
	cameraComponent->SetProjection(72);
	
	movementComponent = CreateComponent<DoodleMovementComponent>();

	crosshair = GetScene()->SpawnGameObject<Crosshair>();

	Sprite* sprite = createSprite("assets/bunny-left@2x.png");
	std::shared_ptr<Sprite> spriteRef;
	spriteRef.reset(sprite);
	spriteComponent->SetSprite(spriteRef);
}

void Doodle::Start()
{
	GameObject::Start();
	auto doodle = GetScene()->GetObject(this);
	spriteComponent->SetOwner(doodle);
	cameraComponent->SetOwner(doodle);
	movementComponent->SetOwner(doodle);

	EventHandler::Get()->BindAction(EInputAction::Move, ETriggerEvent::Triggered, std::bind(&Doodle::Move, this, std::placeholders::_1));
	EventHandler::Get()->BindAction(EInputAction::Shoot, ETriggerEvent::Pressed, std::bind(&Doodle::Shoot, this, std::placeholders::_1));
	boxComponent->OnBeginOverlap.Add(std::bind(&Doodle::OnCollision, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));


	spriteComponent->GetTransform().Scale = { 6.9, 6.9, 1.0 };
	spriteComponent->GetTransform().Translation = { 0.0, 0.7, 0.0 };
	boxComponent->SetHalfSize({ 1.8, 2.5 });
	boxComponent->SetCollisionChannel(ECollisionChannel::Character);
	boxComponent->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Ignore);



	movementComponent->SetGravity(-140); // -140
	movementComponent->SetMaxSpeed(50);
	movementComponent->SetJumpVelocity(70); //70

}

void Doodle::Tick(double DeltaTime)
{
	GameObject::Tick(DeltaTime);
	//std::cout << "FPS: " << 1.0 / DeltaTime << std::endl;
}

Math::Vector2D Doodle::GetVelocity() const
{
	return movementComponent->GetVelocity();
}

void Doodle::AddMovementInput(Math::Vector2D direction)
{
	movementComponent->AddMovementInput(direction);
}

void Doodle::Jump()
{
	movementComponent->Jump();
}

void Doodle::Move(InputValue& value)
{
	AddMovementInput(value.Get<double>() * Math::Vector2D{1, 0});
}

void Doodle::Shoot(InputValue& value)
{

}

void Doodle::OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime)
{
	if (normal.y > 0)
	{
		movementComponent->OnCollision(collisionTime);
		Jump();
	}

}
