#include "Doodle.h"

#include "GameObjects/UI/Crosshair.h"
#include "GameModes/DJGameMode.h"
#include "Projectile.h"
#include "Abilities/ImmunityAbility.h"
#include "Input/EventHandler.h"
#include "Components/DoodleMovementComponent.h"
#include "Components/FollowCameraComponent.h"

#include "Core/Base/Log.h"
#include "Core/Base/AssetManager.h"
#include "Animations/DoodleAnimator.h"


#include "Core/Renderer/Animation.h" // Temporary


Doodle::Doodle() : GameObject()
{
	m_SpriteComponent = CreateComponent<SpriteComponent>();
	m_SpriteComponent->SetupAttachment(GetBoxComponent());

	// Don't need attachment
	m_CameraComponent = CreateComponent<FollowCameraComponent>();
	GetScene()->UseCamera(m_CameraComponent);
	
	m_MovementComponent = CreateComponent<DoodleMovementComponent>();
	m_Crosshair = GetScene()->SpawnGameObject<Crosshair>();

	m_BoxComponent->SetHalfSize({ 1.8, 2.5 });
	m_BoxComponent->SetCollisionChannel(ECollisionChannel::Character);
	m_BoxComponent->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Ignore);

	m_SpriteComponent->GetTransform().Scale = { 6.9, 6.9, 1.0 };
	m_SpriteComponent->GetTransform().Translation = { 0.0, 0.7, 0.0 };

	m_MovementComponent->SetGravity(-140); // -140
	m_MovementComponent->SetMaxSpeed(40);
	m_MovementComponent->SetJumpVelocity(m_DefaultJumpVelocity); //70

	m_SpriteComponent->SetAnimator(std::make_shared<DoodleAnimator>(this));
	 m_SpriteComponent->EnableAnimation();

	OBJECT_LOG_CONSTRUCTOR()
}

Doodle::~Doodle()
{
	OBJECT_LOG_DESTRUCTOR()
}

void Doodle::Start()
{
	GameObject::Start();
	auto doodle = GetScene()->GetObject(this);
	m_SpriteComponent->SetOwner(doodle);
	m_CameraComponent->SetOwner(doodle);
	m_MovementComponent->SetOwner(doodle);

	EventHandler::Get()->BindAction(EInputAction::Move, ETriggerEvent::Triggered, std::bind(&Doodle::Move, this, std::placeholders::_1));
	EventHandler::Get()->BindAction(EInputAction::Shoot, ETriggerEvent::Pressed, std::bind(&Doodle::Shoot, this, std::placeholders::_1));
	m_BoxComponent->OnBeginOverlap.Add(std::bind(&Doodle::OnCollision, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	SetTag("doodle");
}

void Doodle::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);

	if (HasImmunity())
	{
		if (m_ImmunityTimer > m_Immunity->GetTime())
		{
			m_Immunity->Destroy();
			m_Immunity = nullptr;
		}
		else
		{
			m_ImmunityTimer += deltaTime;
			m_Immunity->SetLocation(m_BoxComponent->GetTransform().Translation);
		}
	}

	if (m_bShooting)
	{
		if (m_ShootTimer >= 0.35)
			m_bShooting = false;
		m_ShootTimer += deltaTime;
	}
	if (m_bJumping)
	{
		if (m_JumpTimer >= 0.35)
			m_bJumping = false;
		m_JumpTimer += deltaTime;
	}
}

void Doodle::Destroy()
{
	GameObject::Destroy();
	m_SpriteComponent->Destroy();
	m_MovementComponent->Destroy();
	m_CameraComponent->Destroy();
}

Math::Vector2D Doodle::GetVelocity() const
{
	return m_MovementComponent->GetVelocity();
}

void Doodle::AddMovementInput(Math::Vector2D direction)
{
	m_MovementComponent->AddMovementInput(direction);
	if (m_MovementComponent->GetVelocity().x > 0)
		m_LookHDirection = 1;
	if (m_MovementComponent->GetVelocity().x < 0)
		m_LookHDirection = -1;
}

void Doodle::Jump()
{
	m_MovementComponent->Jump();
}

void Doodle::DisableInput()
{
	m_bInputEnabled = false;
}

void Doodle::EnableInput()
{
	m_bInputEnabled = true;
}

void Doodle::DisablePhysicsCollision()
{
	m_bPhysicsCollisionEnabled = false;
}

void Doodle::EnableCollision()
{
	m_bPhysicsCollisionEnabled = true;
}

int32_t Doodle::GetLifesCount()
{
	return m_LifesCount;
}

int32_t Doodle::GetJumpsCount()
{
	return m_JumpsCount;
}

void Doodle::ResetJumpsCount()
{
	m_JumpsCount = 0;
}

bool Doodle::HasImmunity()
{
	return m_Immunity != nullptr;
}

void Doodle::Move(InputValue& value)
{
	if (m_bInputEnabled)
		AddMovementInput(value.Get<double>() * Math::Vector2D{1, 0});
}

void Doodle::Shoot(InputValue& value)
{
	std::shared_ptr<Projectile> projectile = GetScene()->SpawnGameObject<Projectile>();
	projectile->SetLocation({ GetLocation() + Math::Vector2D{0, 3}, 0 });
	Math::Vector2D direction =  m_Crosshair->GetLocation() - projectile->GetLocation();
	Math::Vector2D leftEdge{ -1, 1 };
	Math::Vector2D rightEdge{ 1, 1 };
	direction = Math::Clamp(Math::Normalize(direction), Math::Normalize(leftEdge), Math::Normalize(rightEdge));
	projectile->Launch(direction, 70);
	m_bShooting = true;
	m_ShootTimer = 0;
}

void Doodle::OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime)
{
	std::string otherTag = otherObject->GetTag();
	if (normal.y > 0 && m_bPhysicsCollisionEnabled)
	{
		if (otherTag == "platform" )
		{
			m_MovementComponent->OnCollision(collisionTime);
			Jump();
			m_JumpsCount++;
			m_bJumping = true;
			m_JumpTimer = 0;
		}
		else if (otherTag == "monster")
		{
			m_MovementComponent->OnCollision(collisionTime);
			m_MovementComponent->SetJumpVelocity(110);
			Jump();
			m_MovementComponent->SetJumpVelocity(m_DefaultJumpVelocity);
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
		m_LifesCount--;
		if (m_LifesCount == 0)
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
		m_Immunity = static_pointer_cast<ImmunityAbility>(otherObject);
		m_Immunity->DisableCollision();
		m_ImmunityTimer = 0;
	}
}
