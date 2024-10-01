#include "MenuGameMode.h"
#include "Framework.h" /* For showCursor() */
#include "Core/World/World.h"
#include "Core/World/CollisionSystem.h"
#include "Core/Components/CameraComponent.h"
#include "Core/Renderer/MySprite.h"
#include "Core/Base/AssetManager.h"

#include "GameObjects/Doodle.h"
#include "GameObjects/UI/MenuBackground.h"
#include "GameObjects/UI/MenuController.h"
#include "GameObjects/UI/PlayButton.h"

#include "Scenes/LevelScene.h"


MenuGameMode::MenuGameMode()
{
	OBJECT_LOG_CONSTRUCTOR()
}

MenuGameMode::~MenuGameMode()
{
	OBJECT_LOG_DESTRUCTOR()
}

void MenuGameMode::Start()
{
	showCursor(true);

	// Spawn Player
	m_Player = GetScene()->SpawnGameObject<MenuController>();
	// Spawn Background
	std::shared_ptr<Background> background = GetScene()->SpawnGameObject<MenuBackground>();
	background->GetSpriteComponent()->GetTransform().Scale = { 36, 54, 1 };
	background->GetSpriteComponent()->GetTransform().Translation = { 0, 0, -1 };

	// Camera
	m_Camera = GetScene()->GetRenderCamera();
	Math::Vector2D camBounds = m_Camera->GetCameraBounds();
	m_HorizontalBounds = { m_Camera->GetTransform().Translation.x - camBounds.x * 0.5, m_Camera->GetTransform().Translation.x + camBounds.x * 0.5 };

	m_PlayButton = GetScene()->SpawnGameObject<PlayButton>();
}


void MenuGameMode::Click(Math::Vector2D mousePos)
{
	bool isClicked = Physics::IsColliding({ mousePos, {0.1, 0.1}, {0, 0} }, m_PlayButton->GetBoxComponent()->GetCollider());

	if (isClicked)
	{
		GetWorld()->OpenScene<LevelScene>();
	}
}
