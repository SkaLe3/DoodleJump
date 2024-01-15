#include "Doodle.h"
#include "Components/SpriteComponent.h"

// TESTING
#include <iostream>
#include "World/World.h"
#include "Input/EventHandler.h"
#include "Input/TriggerEvent.h"
#include "Input/InputAction.h"
#include "Input/InputValue.h"
#include <functional>
Doodle::Doodle() : GameObject()
{
	spriteComponent = CreateComponent<SpriteComponent>();
}

void Doodle::Start()
{
	EventHandler::Get()->BindAction(EInputAction::Move, ETriggerEvent::Triggered, std::bind(&Doodle::Move, this, std::placeholders::_1));
}

void Doodle::Tick(double DeltaTime)
{
	std::cout << "TICK" << std::endl;
}

void Doodle::Move(InputValue& value)
{
	this->GetTransform().Translation.x += 500 * value.Get<double>() * GetWorld()->GetDeltaTime();
}
