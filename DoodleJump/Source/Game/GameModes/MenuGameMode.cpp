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
#include "DoodleGameInstance.h"

#include "UI/UI.h"


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
	m_HighScore = DoodleGameInstance::Get<DoodleGameInstance>().GetHighScore();
	m_LastScore = DoodleGameInstance::Get<DoodleGameInstance>().GetLastScore();
	m_HighPlat = DoodleGameInstance::Get<DoodleGameInstance>().GetHighestReachedPlatform();
	m_LastPlat = DoodleGameInstance::Get<DoodleGameInstance>().GetLastPassedPlatform();


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

	m_HighScoreWidget = UI::CreateNumberWidget({ 4, 30 }, 6);
	m_HighPlatformWidget = UI::CreateNumberWidget({4, 28}, 6);
	m_LastScoreWidget = UI::CreateNumberWidget({ -16, 30 }, 6);
	m_LastPlatformWidget = UI::CreateNumberWidget({-16, 28}, 6);

	UI::CreateWidget("S_DistanceIcon", { 14, 30 }, { 2, 2 }, 2);
	UI::CreateWidget("S_DistanceIcon", { -6, 30 }, { 2, 2 }, 2);
	UI::CreateWidget("S_Bamboo", { 15, 28 }, { 4, 1.08 }, 2);
	UI::CreateWidget("S_Bamboo", { -5, 28 }, { 4, 1.08 }, 2);

}


void MenuGameMode::Tick(double deltaTime)
{
	// Doesnt work in Start
	int32_t highScore = DoodleGameInstance::Get<DoodleGameInstance>().GetHighScore();
	int32_t lastScore = DoodleGameInstance::Get<DoodleGameInstance>().GetLastScore();
	int32_t highPlat = DoodleGameInstance::Get<DoodleGameInstance>().GetHighestReachedPlatform();
	int32_t lastPlat = DoodleGameInstance::Get<DoodleGameInstance>().GetLastPassedPlatform();
	UI::UpdateWidget(m_HighScoreWidget, highScore);
	UI::UpdateWidget(m_LastScoreWidget, lastScore);
	UI::UpdateWidget(m_HighPlatformWidget, highPlat);
	UI::UpdateWidget(m_LastPlatformWidget, lastPlat);
}

void MenuGameMode::Click(Math::Vector2D mousePos)
{
	bool isClicked = Physics::IsColliding({ mousePos, {0.1, 0.1}, {0, 0} }, m_PlayButton->GetBoxComponent()->GetCollider());

	if (isClicked)
	{
		GetWorld()->OpenScene<LevelScene>();
	}
}
