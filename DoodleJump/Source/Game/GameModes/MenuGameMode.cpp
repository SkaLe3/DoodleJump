#include "MenuGameMode.h"
#include "Framework.h" /* For showCursor() */
#include "Core/World/World.h"
#include "Core/World/CollisionSystem.h"
#include "Core/Components/CameraComponent.h"
#include "Core/Renderer/MySprite.h"
#include "Core/Base/AssetManager.h"

#include "GameObjects/DoodleController.h"
#include "GameObjects/UI/MenuBackground.h"
#include "GameObjects/UI/MenuController.h"
#include "GameObjects/UI/PlayButton.h"
#include "GameObjects/Platform.h"

#include "Scenes/LevelScene.h"
#include "DoodleGameInstance.h"

#include "UI/UI.h"


MenuGameMode::MenuGameMode()
{
	m_MaxViewArea = {36, 72};

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
	background->GetSpriteComponent()->GetTransform().Translation = { 0, 43.5, -1 };
	background = GetScene()->SpawnGameObject<MenuBackground>();
	background->GetSpriteComponent()->SetSprite(AssetManager::Get().GetAsset<MySprite>("S_MenuBgBottom"));
	background->GetSpriteComponent()->GetTransform().Translation = { 0, -10, -0.8 };
	// TODO: make 35 cells in width

	// Camera
	m_Camera = GetScene()->GetRenderCamera();
	int32_t visibleHorizontalSize;
	if (m_Camera->GetAspectRatio() >= m_MinAspectRatio)
		visibleHorizontalSize = (int32_t)m_MaxViewArea.x;
	else
		visibleHorizontalSize = (int32_t)(m_MinAspectRatio / m_Camera->GetAspectRatio() * m_MaxViewArea.x);
	m_Camera->SetProjection(visibleHorizontalSize);

	Math::Vector2D camBounds = m_Camera->GetCameraBounds();
	m_ViewArea = { std::min(m_MaxViewArea.x, camBounds.x), std::min(m_MaxViewArea.y, camBounds.y)};

	m_HorizontalBounds = { m_Camera->GetTransform().Translation.x - m_ViewArea.x * 0.5, m_Camera->GetTransform().Translation.x + m_ViewArea.x * 0.5 };

	m_PlayButton = GetScene()->SpawnGameObject<PlayButton>();
	m_PlayButton->GetTransform().Translation = { -6, 14, 0 };

	m_HighScoreWidget = UI::CreateNumberWidget({ 1.5, -2 }, 6);
	m_HighPlatformWidget = UI::CreateNumberWidget({ 1.5, -4 }, 6);
	m_LastScoreWidget = UI::CreateNumberWidget({ 1.5, -14 }, 6);
	m_LastPlatformWidget = UI::CreateNumberWidget({ 1.5, -16 }, 6);


	UI::CreateWidget("S_ScoreWhite", {8, 6.5}, {12, 6}, 2);
	UI::CreateWidget("S_HighWhite", {4, 2}, {8, 4}, 2);
	UI::CreateWidget("S_ScoreWhite", {12, 2}, {8, 4}, 2);
	UI::CreateWidget("S_LastWhite", {4, -10}, {8, 4}, 2);
	UI::CreateWidget("S_ScoreWhite", {12, -10}, {8, 4}, 2);

	UI::CreateWidget("S_DistanceIcon", { 12, -2 }, { 2, 2 }, 2);
	UI::CreateWidget("S_DistanceIcon", { 12, -14 }, { 2, 2 }, 2);
	UI::CreateWidget("S_PlatformUI", { 12.5, -4 }, { 4.5, 4.5 }, 2);
	UI::CreateWidget("S_PlatformUI", { 12.5, -16 }, { 4.5, 4.5 }, 2);

	UI::CreateWidget("S_BlackBar", { -68, 0 }, { 100, 200 }, 3);
	UI::CreateWidget("S_BlackBar", { 68, 0 }, { 100, 200 }, 3);
	UI::CreateWidget("S_BlackBar", { 0, 86 }, { 100, 100 }, 3);
	UI::CreateWidget("S_BlackBar", { 0, -86 }, { 100, 100 }, 3);

	UI::CreateWidget("S_BlackBar", { 0, 0 }, { 100, 100 }, -10);

	UI::CreateWidget("S_DoodleJump", { -0, 26 }, { 30, 6 }, 2);


	std::shared_ptr<Platform> platform = GetScene()->SpawnGameObject<Platform>();
	platform->SetTag("platform");
	platform->SetLocation({-10, -18, 0});
	platform->GetSpriteComponent()->SetSprite(AssetManager::Get().GetAsset<MySprite>("S_PlatformUI"));
	platform->GetSpriteComponent()->GetTransform().Scale = {6.8, 6.8, 1};

	std::shared_ptr<Doodle> doodle = static_pointer_cast<Doodle>(GetScene()->SpawnGameObject<Doodle>());
	doodle->SetLocation({-10, -29, 1});
	doodle->Jump();
	GetScene()->UseCamera(m_Camera);

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
