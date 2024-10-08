#include "MenuController.h"
#include "Core/Components/CameraComponent.h"
#include "Core/Input/EventHandler.h"
#include "Core/World/CollisionSystem.h"
#include "Core/Components/BoxCollider.h"
#include "Core/Entities/CameraObject.h"
#include "GameModes/MenuGameMode.h"

MenuController::MenuController()
{
	// Don't need attachment
	m_Camera = GetScene()->SpawnGameObject<CameraObject>();
	auto camera = m_Camera.lock()->GetCameraComponent();

	OBJECT_LOG_CONSTRUCTOR()
}

MenuController::~MenuController()
{
	OBJECT_LOG_DESTRUCTOR()
}

void MenuController::Start()
{
	GameObject::Start();
	EventHandler::Get()->BindAction(EInputAction::Shoot, ETriggerEvent::Pressed, std::bind(&MenuController::Click, this, std::placeholders::_1));
	GetBoxComponent()->SetCollisionEnabled(false);
}

void MenuController::Tick(double deltaTime)
{

}

void MenuController::Destroy()
{
	GameObject::Destroy();	   
}

void MenuController::Click(InputValue& value)
{
	Math::Vector2D mousePos = GetScene()->GetMousePosition();
	static_pointer_cast<MenuGameMode>(GetGameMode())->Click(mousePos);
}
