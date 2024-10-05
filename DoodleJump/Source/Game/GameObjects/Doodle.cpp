#include "DoodleController.h"
#include "Core/Base/Log.h"
#include "Core/Base/AssetManager.h"
#include "GameModes/DJGameMode.h"
#include "GameObjects/Abilities/ImmunityAbility.h"
#include "GameObjects/Monster.h"
#include "Components/DoodleMovementComponent.h"
#include "Animations/DoodleAnimator.h"



Doodle::Doodle() : GameObject()
{
	m_SpriteComponent = CreateComponent<SpriteComponent>();
	auto sprite = GetSpriteComponent();
	sprite->SetupAttachment(GetBoxComponent());
	sprite->GetTransform().Scale = { 6.9, 6.9, 1.0 };
	sprite->GetTransform().Translation = { 0.0, 0.7, 0.0 };
	sprite->SetAnimator(std::make_shared<DoodleAnimator>(this));
	sprite->EnableAnimation();

	m_MovementComponent = CreateComponent<DoodleMovementComponent>();
	auto movement = GetMovementComponent();
	movement->SetGravity(-140); // -140
	movement->SetMaxSpeed(40);
	movement->SetJumpVelocity(m_DefaultJumpVelocity); //70

	auto box = GetBoxComponent();
	box->SetHalfSize({ 1.8, 2.5 });
	box->SetCollisionChannel(ECollisionChannel::Character);
	box->SetCollisionResponce(ECollisionChannel::Character, ECollisionResponse::Ignore);
	OBJECT_LOG_DESTRUCTOR()
}

Doodle::~Doodle()
{
	OBJECT_LOG_DESTRUCTOR()
}

void Doodle::Start()
{
	GameObject::Start();

	GetSpriteComponent()->SetOwner(GetSelf());
	GetMovementComponent()->SetOwner(GetSelf());
	GetBoxComponent()->OnBeginOverlap.Add(std::bind(&Doodle::OnCollision,
													this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	m_LookHDirection = 1;
	SetTag("doodle");
}

void Doodle::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);

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
}

Math::Vector2D Doodle::GetVelocity() const
{
	return GetMovementComponent()->GetVelocity();
}

bool Doodle::HasImmunity()
{
	if (auto immunity = m_Immunity.lock())
	{
		return immunity->IsActive();
	}
	return false;
}

void Doodle::Jump()
{
	GetMovementComponent()->Jump();
}

void Doodle::DisablePhysicsCollision()
{
	m_bPhysicsCollisionEnabled = false;
}

void Doodle::EnableCollision()
{
	m_bPhysicsCollisionEnabled = true;
}

void Doodle::OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime)
{
	std::string otherTag = otherObject->GetTag();
	if (normal.y > 0 && m_bPhysicsCollisionEnabled)
	{
		auto movement = GetMovementComponent();
		if (otherTag == "platform")
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
			std::static_pointer_cast<Monster>(otherObject)->Kill();
		}
	}
	std::shared_ptr<DJGameMode> gameMode = dynamic_pointer_cast<DJGameMode>(GetGameMode());
	if (gameMode)
	{

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
			auto immunity = m_Immunity.lock();
			immunity->Activate();
			immunity->GetBoxComponent()->SetupAttachment(GetBoxComponent());
			immunity->SetLocation({0, 0}); // Relative;
		}
	}
}
