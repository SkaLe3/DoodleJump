#include "MenuController.h"
#include "Core/Components/CameraComponent.h"
#include "Core/Input/EventHandler.h"
#include "Core/World/CollisionSystem.h"
#include "Core/Components/BoxCollider.h"
#include "GameModes/MenuGameMode.h"

MenuController::MenuController()
{
	// Don't need attachment
	m_CameraComponent = CreateComponent<CameraComponent>();
	GetScene()->UseCamera(m_CameraComponent);
	m_CameraComponent->SetProjection(36);
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
	m_CameraComponent->SetOwner(controller);

	EventHandler::Get()->BindAction(EInputAction::Shoot, ETriggerEvent::Pressed, std::bind(&MenuController::Click, this, std::placeholders::_1));
	m_BoxComponent->SetCollisionEnabled(false);
}

void MenuController::Tick(double deltaTime)
{

}

void MenuController::Destroy()
{
	GameObject::Destroy();
	m_CameraComponent->Destroy();	   
}

void MenuController::Click(InputValue& value)
{
	Math::Vector2D mousePos = GetScene()->GetMousePosition();
	static_pointer_cast<MenuGameMode>(GetGameMode())->Click(mousePos);
}
