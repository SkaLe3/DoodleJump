#include "Doodle.h"
#include "Core/Input/EventHandler.h"
#include "Core/Base/Log.h"
#include "Core/Base/AssetManager.h"

#include "GameObjects/UI/Crosshair.h"
#include "GameModes/DJGameMode.h"
#include "GameObjects/Projectile.h"
#include "GameObjects/Abilities/ImmunityAbility.h"
#include "Components/DoodleMovementComponent.h"
#include "Components/FollowCameraComponent.h"
#include "Animations/DoodleAnimator.h"


Doodle::Doodle() : GameObject()
{
	m_SpriteComponent = CreateComponent<SpriteComponent>();
	auto sprite = GetSpriteComponent();
	sprite->SetupAttachment(GetBoxComponent());

	// Don't need attachment
	m_CameraComponent = CreateComponent<FollowCameraComponent>();
	GetScene()->UseCamera(m_CameraComponent);
	
	m_MovementComponent = CreateComponent<DoodleMovementComponent>();
	auto movement = GetMovementComponent();
	m_Crosshair = GetScene()->SpawnGameObject<Crosshair>();

	auto box = GetBoxComponent();
	box->SetHalfSize({ 1.8, 2.5 });
	box->SetCollisionChannel(ECollisionChannel::Character);
	box->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Ignore);

	sprite->GetTransform().Scale = { 6.9, 6.9, 1.0 };
	sprite->GetTransform().Translation = { 0.0, 0.7, 0.0 };

	movement->SetGravity(-140); // -140
	movement->SetMaxSpeed(40);
	movement->SetJumpVelocity(m_DefaultJumpVelocity); //70

	sprite->SetAnimator(std::make_shared<DoodleAnimator>(this));
	sprite->EnableAnimation();

	OBJECT_LOG_CONSTRUCTOR()
}

Doodle::~Doodle()
{
	OBJECT_LOG_DESTRUCTOR()
}

void Doodle::Start()
{
	GameObject::Start();

	GetSpriteComponent()->SetOwner(GetSelf());
	GetCameraComponent()->SetOwner(GetSelf());
	GetMovementComponent()->SetOwner(GetSelf());

	EventHandler::Get()->BindAction(EInputAction::Move, ETriggerEvent::Triggered, std::bind(&Doodle::Move, this, std::placeholders::_1));
	EventHandler::Get()->BindAction(EInputAction::Shoot, ETriggerEvent::Pressed, std::bind(&Doodle::Shoot, this, std::placeholders::_1));
	GetBoxComponent()->OnBeginOverlap.Add(std::bind(&Doodle::OnCollision, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	SetTag("doodle");
}

void Doodle::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);

	if (auto immunity = GetImmunity())
	{
		if (m_ImmunityTimer > immunity->GetTime())
		{
			immunity->Destroy();
			immunity = nullptr;
		}
		else
		{
			m_ImmunityTimer += deltaTime;
			immunity->SetLocation(GetBoxComponent()->GetTransform().Translation);
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
	GetSpriteComponent()->Destroy();
	GetMovementComponent()->Destroy();
	GetCameraComponent()->Destroy();
}

Math::Vector2D Doodle::GetVelocity() const
{
	return GetMovementComponent()->GetVelocity();
}

void Doodle::AddMovementInput(Math::Vector2D direction)
{
	auto movement = GetMovementComponent();
	movement->AddMovementInput(direction);
	if (movement->GetVelocity().x > 0)
		m_LookHDirection = 1;
	if (movement->GetVelocity().x < 0)
		m_LookHDirection = -1;
}

void Doodle::Jump()
{
	GetMovementComponent()->Jump();
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

std::shared_ptr<ImmunityAbility> Doodle::GetImmunity()
{
	return m_Immunity.lock();
}

void Doodle::Move(InputValue& value)
{
	if (m_bInputEnabled)
		AddMovementInput(value.Get<double>() * Math::Vector2D{1, 0});
}

void Doodle::Shoot(InputValue& value)
{
	// Option: Could use a pool of projectiles instead of spawning new ones, but not doing that for now.
	std::shared_ptr<Projectile> projectile = GetScene()->SpawnGameObject<Projectile>();
	projectile->SetLocation({ GetLocation() + Math::Vector2D{0, 3}, 0 });
	auto crosshair = m_Crosshair.lock();
	Math::Vector2D direction = crosshair->GetLocation() - projectile->GetLocation();
	direction.y = std::abs(direction.y);
	direction = Math::Normalize(direction);

	float dotProduct = Math::Dot(direction, {0, 1});
	float angle = std::acos(dotProduct);
	float clampAngle = M_PI / 3;
	if (std::abs(angle) > clampAngle)
	{
		direction = direction.x > 0 ? Math::Vector2D{1, 1} : Math::Vector2D{-1, 1};
		direction = Math::Normalize(direction);
	}

	projectile->Launch(direction, 70);
	m_bShooting = true;
	m_ShootTimer = 0;
}

void Doodle::OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime)
{
	std::string otherTag = otherObject->GetTag();
	if (normal.y > 0 && m_bPhysicsCollisionEnabled)
	{
		auto movement = GetMovementComponent();
		if (otherTag == "platform" )
		{
			movement->OnCollision(collisionTime);
			Jump();
			m_JumpsCount++;
			m_bJumping = true;
			m_JumpTimer = 0;
		}
		else if (otherTag == "monster")
		{
			movement->OnCollision(collisionTime);
			movement->SetJumpVelocity(110);
			Jump();
			movement->SetJumpVelocity(m_DefaultJumpVelocity);
			otherObject->Destroy();
		}
	}
	std::shared_ptr<DJGameMode> gameMode = static_pointer_cast<DJGameMode>(GetGameMode());
	if (otherTag == "left wall")
	{
		gameMode->TeleportToRightWall(GetSelf());
	}
	if (otherTag == "right wall")
	{
		gameMode->TeleportToLeftWall(GetSelf());
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
		auto immunity = GetImmunity();
		immunity->DisableCollision();
		m_ImmunityTimer = 0;
	}
}
