#include "MenuGameMode.h"
#include "World/World.h"
#include "World/Scene.h"
#include "World/CollisionSystem.h"

#include "GameObjects/Doodle.h"
#include "GameObjects/UI/MenuBackground.h"
#include "Components/CameraComponent.h"

#include "Renderer/MySprite.h"
#include "GameObjects/UI/MenuController.h"
#include "GameObjects/UI/PlayButton.h"

#include "Scenes/LevelScene.h"
#include "Core/Base/AssetManager.h"

#include "Framework.h" /* For showCursor() */

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
	background->GetSprite()->GetTransform().Scale = { 36, 54, 1 };
	background->GetSprite()->GetTransform().Translation = { 0, 0, -1 };

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
