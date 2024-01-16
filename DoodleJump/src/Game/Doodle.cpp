#include "Doodle.h"
#include "Components/SpriteComponent.h"
#include "Math/Vector2D.h"
// TESTING
#include <iostream>
#include "World/World.h"
#include "Input/EventHandler.h"
#include "Input/TriggerEvent.h"
#include "Input/InputAction.h"
#include "Input/InputValue.h"
#include "Components/DoodleMovementComponent.h"
#include "Components/CameraComponent.h"
#include <functional>
Doodle::Doodle() : GameObject()
{
	spriteComponent = CreateComponent<SpriteComponent>();
	spriteComponent->SetupAttachment(GetBoxComponent());

	// Don't need attachment
	cameraComponent = CreateComponent<CameraComponent>();
	
	movementComponent = CreateComponent<DoodleMovementComponent>();
}

void Doodle::Start()
{
	GameObject::Start();

	EventHandler::Get()->BindAction(EInputAction::Move, ETriggerEvent::Triggered, std::bind(&Doodle::Move, this, std::placeholders::_1));
	cameraComponent->SetProjection(72);

	GetSpriteComponent()->GetTransform().Scale = { 6.9, 6.9, 1.0 };
	GetSpriteComponent()->GetTransform().Translation = { 0.0, 0.7, 0.0 };
	GetBoxComponent()->SetSize({ 3.6, 5 });
}

void Doodle::Tick(double DeltaTime)
{
	GameObject::Tick(DeltaTime);
}

Math::Vector2D Doodle::GetVelocity() const
{
	return movementComponent->GetVelocity();
}

void Doodle::Move(InputValue& value)
{
	//this->GetTransform().Translation.x += 55 * value.Get<double>() * GetWorld()->GetDeltaTime();
	//AddMovementInput(value.Get<double>() * Math::Vector2D{1, 0});
}
