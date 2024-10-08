#include "DoodleController.h"
#include "Core/Input/EventHandler.h"
#include "GameObjects/UI/Crosshair.h"
#include "GameObjects/Projectile.h"
#include "GameObjects/Abilities/ImmunityAbility.h"
#include "Components/DoodleMovementComponent.h"
#include "Components/FollowCameraComponent.h"



DoodleController::DoodleController() : Doodle()
{
	// Don't need attachment
	m_CameraComponent = CreateComponent<FollowCameraComponent>();
	GetScene()->UseCamera(m_CameraComponent);
	
	m_Crosshair = GetScene()->SpawnGameObject<Crosshair>();
}


void DoodleController::Start()
{
	Doodle::Start();

	GetCameraComponent()->SetOwner(GetSelf());
	EventHandler::Get()->BindAction(EInputAction::Move, ETriggerEvent::Triggered, std::bind(&DoodleController::Move, this, std::placeholders::_1));
	EventHandler::Get()->BindAction(EInputAction::Shoot, ETriggerEvent::Pressed, std::bind(&DoodleController::Shoot, this, std::placeholders::_1));
}

void DoodleController::Tick(double deltaTime)
{
	Doodle::Tick(deltaTime);

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

}

void DoodleController::Destroy()
{
	 Doodle::Destroy();

	GetCameraComponent()->Destroy();
}


void DoodleController::AddMovementInput(Math::Vector2D direction)
{
	auto movement = GetMovementComponent();
	movement->AddMovementInput(direction);
	if (movement->GetVelocity().x > 0)
		m_LookHDirection = 1;
	if (movement->GetVelocity().x < 0)
		m_LookHDirection = -1;
}

void DoodleController::DisableInput()
{
	m_bInputEnabled = false;
}

void DoodleController::EnableInput()
{
	m_bInputEnabled = true;
}


int32_t DoodleController::GetLifesCount()
{
	return m_LifesCount;
}

int32_t DoodleController::GetJumpsCount()
{
	return m_JumpsCount;
}

void DoodleController::ResetJumpsCount()
{
	m_JumpsCount = 0;
}


void DoodleController::Move(InputValue& value)
{
	if (m_bInputEnabled)
		AddMovementInput(value.Get<double>() * Math::Vector2D{1, 0});
}

void DoodleController::Shoot(InputValue& value)
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
	float clampAngle = 0.22143;
	if (std::abs(angle) > clampAngle)
	{
		direction = direction.x > 0 ? Math::Vector2D{1, 2.5} : Math::Vector2D{-1, 2.5};
		direction = Math::Normalize(direction);
	}

	projectile->Launch(direction, 70);
	m_bShooting = true;
	m_ShootTimer = 0;
}


