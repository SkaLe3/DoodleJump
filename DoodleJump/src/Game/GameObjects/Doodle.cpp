#include "Doodle.h"

#include "Crosshair.h"
#include "GameModes/DJGameMode.h"
#include "Projectile.h"
#include "Abilities/ImmunityAbility.h"
#include "Input/EventHandler.h"
#include "Components/DoodleMovementComponent.h"
#include "Components/FollowCameraComponent.h"

#include "Framework.h"


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

	boxComponent->SetHalfSize({ 1.8, 2.5 });
	boxComponent->SetCollisionChannel(ECollisionChannel::Character);
	boxComponent->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Ignore);

	spriteComponent->GetTransform().Scale = { 6.9, 6.9, 1.0 };
	spriteComponent->GetTransform().Translation = { 0.0, 0.7, 0.0 };

	movementComponent->SetGravity(-140); // -140
	movementComponent->SetMaxSpeed(40);
	movementComponent->SetJumpVelocity(defaultJumpVelocity); //70

	std::shared_ptr<AnimationMachine> animationMachine = std::make_shared<AnimationMachine>();
	std::shared_ptr<std::vector<std::shared_ptr<MySprite>>> animStateLeft = std::make_shared<std::vector<std::shared_ptr<MySprite>>>();
	std::shared_ptr<std::vector<std::shared_ptr<MySprite>>> animStateRight = std::make_shared<std::vector<std::shared_ptr<MySprite>>>();
	animStateLeft->emplace_back(std::make_shared<MySprite>("assets/player-left@2x.png"));
	animStateRight->emplace_back(std::make_shared<MySprite>("assets/player-right@2x.png"));

	(*animationMachine)["left"] = std::make_pair(animStateLeft, 1);
	(*animationMachine)["right"] = std::make_pair(animStateRight, 1);

	spriteComponent->SetAnimationMachine(animationMachine);
	spriteComponent->EnableAnimation();
	spriteComponent->SwitchAnimationState("left");


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

	SetTag("doodle");
}

void Doodle::Tick(double DeltaTime)
{
	GameObject::Tick(DeltaTime);

	if (HasImmunity())
	{
		if (immunityTimer > immunity->GetTime())
		{
			immunity->Destroy();
			immunity = nullptr;
		}
		else
		{
			immunityTimer += DeltaTime;
			immunity->SetLocation(boxComponent->GetTransform().Translation);
		}
	}
}

void Doodle::Destroy()
{
	GameObject::Destroy();
	spriteComponent->Destroy();
	movementComponent->Destroy();
}

Math::Vector2D Doodle::GetVelocity() const
{
	return movementComponent->GetVelocity();
}

void Doodle::AddMovementInput(Math::Vector2D direction)
{
	movementComponent->AddMovementInput(direction);
	if (movementComponent->GetVelocity().x > 0)
		spriteComponent->SwitchAnimationState("right");
	if (movementComponent->GetVelocity().x < 0)
		spriteComponent->SwitchAnimationState("left");
}

void Doodle::Jump()
{
	movementComponent->Jump();
}

void Doodle::DisableInput()
{
	bInputEnabled = false;
}

void Doodle::EnableInput()
{
	bInputEnabled = true;
}

void Doodle::DisablePhysicsCollision()
{
	bPhysicsCollisionEnabled = false;
}

void Doodle::EnableCollision()
{
	bPhysicsCollisionEnabled = true;
}

int32_t Doodle::GetLifesCount()
{
	return lifesCount;
}

int32_t Doodle::GetJumpsCount()
{
	return jumpsCount;
}

void Doodle::ResetJumpsCount()
{
	jumpsCount = 0;
}

bool Doodle::HasImmunity()
{
	return immunity != nullptr;
}

void Doodle::Move(InputValue& value)
{
	if (bInputEnabled)
		AddMovementInput(value.Get<double>() * Math::Vector2D{1, 0});
}

void Doodle::Shoot(InputValue& value)
{
	std::shared_ptr<Projectile> projectile = GetScene()->SpawnGameObject<Projectile>();
	projectile->SetLocation({ GetLocation() + Math::Vector2D{0, 3}, 0 });
	Math::Vector2D direction =  crosshair->GetLocation() - projectile->GetLocation();
	Math::Vector2D leftEdge{ -1, 1 };
	Math::Vector2D rightEdge{ 1, 1 };
	direction = Math::Clamp(Math::Normalize(direction), Math::Normalize(leftEdge), Math::Normalize(rightEdge));
	projectile->Launch(direction, 70);
}

void Doodle::OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime)
{
	std::string otherTag = otherObject->GetTag();
	if (normal.y > 0 && bPhysicsCollisionEnabled)
	{
		if (otherTag == "platform" )
		{
			movementComponent->OnCollision(collisionTime);
			Jump();
			jumpsCount++;
		}
		else if (otherTag == "monster")
		{
			movementComponent->OnCollision(collisionTime);
			movementComponent->SetJumpVelocity(110);
			Jump();
			movementComponent->SetJumpVelocity(defaultJumpVelocity);
			otherObject->Destroy();
		}
	}
	std::shared_ptr<DJGameMode> gameMode = static_pointer_cast<DJGameMode>(GetGameMode());
	if (otherTag == "left wall")
	{
		gameMode->TeleportToRightWall(GetScene()->GetObject(this));
	}
	if (otherTag == "right wall")
	{
		gameMode->TeleportToLeftWall(GetScene()->GetObject(this));
	}
	if (otherTag == "floor")
	{
		lifesCount--;
		if (lifesCount == 0)
		{
			gameMode->KillDoodle();
			gameMode->GameOver();
		}
		else
		{
			gameMode->RespawnPlayer();
		}
	}
	if (otherTag == "immunity")
	{
		immunity = static_pointer_cast<ImmunityAbility>(otherObject);
		immunity->DisableCollision();
		immunityTimer = 0;
	}

}
