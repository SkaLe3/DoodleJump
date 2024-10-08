#include "DoodleController.h"
#include "Core/Input/EventHandler.h"
#include "GameObjects/UI/Crosshair.h"
#include "GameObjects/Projectile.h"
#include "GameObjects/Abilities/ImmunityAbility.h"
#include "GameObjects/CameraObject.h"
#include "Components/DoodleMovementComponent.h"


DoodleController::DoodleController() : Doodle()
{
	m_Crosshair = GetScene()->SpawnGameObject<Crosshair>();
	m_Camera = GetScene()->SpawnGameObject<CameraObject>();
}


void DoodleController::Start()
{
	Doodle::Start();

	EventHandler::Get()->BindAction(EInputAction::Move, ETriggerEvent::Triggered, std::bind(&DoodleController::Move, this, std::placeholders::_1));
	EventHandler::Get()->BindAction(EInputAction::Shoot, ETriggerEvent::Pressed, std::bind(&DoodleController::Shoot, this, std::placeholders::_1));
}

void DoodleController::Tick(double deltaTime)
{
	Doodle::Tick(deltaTime);

	if (auto camera = m_Camera.lock())
	{

		Math::Vector2D doodleLocation = GetLocation();
		if (doodleLocation.y >= camera->GetWorldTransform().Translation.y)
			camera->GetTransform().Translation.y = doodleLocation.y;
	}


}

void DoodleController::Destroy()
{
	Doodle::Destroy();

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
		AddMovementInput(value.Get<double>() * Math::Vector2D{ 1, 0 });
}

void DoodleController::Shoot(InputValue& value)
{
	if (!m_bInputEnabled)
		return;
	// Option: Could use a pool of projectiles instead of spawning new ones, but not doing that for now.
	std::shared_ptr<Projectile> projectile = GetScene()->SpawnGameObject<Projectile>();
	projectile->SetLocation({ GetLocation() + Math::Vector2D{0, 3}, 0 });
	auto crosshair = m_Crosshair.lock();
	Math::Vector2D direction = crosshair->GetLocation() - projectile->GetLocation();
	direction.y = std::abs(direction.y);
	direction = Math::Normalize(direction);

	float dotProduct = Math::Dot(direction, { 0, 1 });
	float angle = std::acos(dotProduct);
	float clampAngle = 0.22143;
	if (std::abs(angle) > clampAngle)
	{
		direction = direction.x > 0 ? Math::Vector2D{ 1, 2.5 } : Math::Vector2D{ -1, 2.5 };
		direction = Math::Normalize(direction);
	}

	projectile->Launch(direction, 70);
	m_bShooting = true;
	m_ShootTimer = 0;
}


