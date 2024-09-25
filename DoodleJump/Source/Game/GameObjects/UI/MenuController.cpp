#include "MenuController.h"
#include "Components/CameraComponent.h"
#include "Input/EventHandler.h"
#include "World/CollisionSystem.h"
#include "Components/BoxCollider.h"
#include "GameModes/MenuGameMode.h"

#include <iostream>

MenuController::MenuController()
{
	// Don't need attachment
	cameraComponent = CreateComponent<CameraComponent>();
	GetScene()->UseCamera(cameraComponent);
	cameraComponent->SetProjection(72);
	OBJECT_LOG_CONSTRUCTOR()
}

MenuController::~MenuController()
{
	OBJECT_LOG_DESTRUCTOR()
}

void MenuController::Start()
{
	GameObject::Start();
	auto controller = GetScene()->GetObject(this);
	cameraComponent->SetOwner(controller);

	
	EventHandler::Get()->BindAction(EInputAction::Shoot, ETriggerEvent::Pressed, std::bind(&MenuController::Click, this, std::placeholders::_1));
	
	boxComponent->SetCollisionEnabled(false);
}

void MenuController::Tick(double deltaTime)
{

}

void MenuController::Destroy()
{
	GameObject::Destroy();
	cameraComponent->Destroy();	   
}

void MenuController::Click(InputValue& value)
{
	Math::Vector2D mousePos = GetScene()->GetMousePosition();

	static_pointer_cast<MenuGameMode>(GetGameMode())->Click(mousePos);

}
