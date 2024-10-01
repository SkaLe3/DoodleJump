#include "DJGameMode.h"

#include "Framework.h"
#include "Core/Base/AssetManager.h"
#include "Core/Components/CameraComponent.h"

#include "GameObjects/Doodle.h"
#include "GameObjects/UI/LevelBackground.h"
#include "GameObjects/PlatformSpawner.h"
#include "GameObjects/Monster.h"
#include "GameObjects/Abilities/ImmunityAbility.h"
#include "GameObjects/UI/NumberWidget.h"
#include "GameObjects/UI/SpriteWidget.h"
#include "Components/UI/NumberComponent.h"
#include "Scenes/MenuScene.h"

DJGameMode::DJGameMode()
{
	OBJECT_LOG_CONSTRUCTOR()
}

DJGameMode::~DJGameMode()
{
	OBJECT_LOG_DESTRUCTOR()
}

void DJGameMode::Start()
{
	StartGame();
}

void DJGameMode::Tick(double deltaTime)
{
	Math::Vector camPos = m_Camera->GetTransform().Translation;

	m_RightWall->GetBoxComponent()->GetTransform().Translation.y = camPos.y;
	m_LeftWall->GetBoxComponent()->GetTransform().Translation.y = camPos.y;
	m_Floor->GetBoxComponent()->GetTransform().Translation.y = camPos.y - 2 - m_ViewArea.y * 0.5;

	UpdateWidget(m_DistanceScoreWidget, m_DistanceScore, std::max((int32_t)m_Player->GetLocation().y, m_DistanceScore));
	UpdateWidget(m_PlatformScoreWidget, m_PlatformScore, m_PlatformSpawner->GetPassedPlatformCount());
	UpdateWidget(m_LifesWidget, m_PlayerLifes, m_Doodle->GetLifesCount());

	bool platformSet = false;
	if (m_PlatformSpawner->GetLastSetPlatformLocation().y - m_DistanceScore < m_ViewArea.y / 2)
	{
		platformSet = m_PlatformSpawner->SetNextPlatform(m_DistanceScore);
	}

	if (platformSet && m_EnemySpawnDistribution(m_RandomEngine))
		SpawnEnemy();

	if (platformSet && m_Doodle->GetJumpsCount() >= m_AbilitySpawnFrequency)
	{
		m_Doodle->ResetJumpsCount();
		SpawnAbility();
	}
}

void DJGameMode::Destroy()
{

}

void DJGameMode::UpdateWidget(std::shared_ptr<NumberWidget> widget, int32_t& value, int32_t newValue)
{
	if (value != newValue)
	{
		widget->Update(newValue);
		value = newValue;
	}
}

void DJGameMode::CreateWidget(const std::string& assetName, Math::Vector2D coords, Math::Vector2D scale, double zLocation)
{
	std::shared_ptr<SpriteWidget> sprite = GetScene()->SpawnGameObject<SpriteWidget>();
	sprite->SetCoordinates(coords);
	std::shared_ptr<SpriteComponent> sc = sprite->GetSprite();
	sc->SetSprite(AssetManager::Get().GetAsset<MySprite>(assetName));
	sc->GetTransform().Scale = { scale, 1 };
	sc->GetTransform().Translation.z = zLocation;
}

void DJGameMode::TeleportToRightWall(std::shared_ptr<GameObject> object)
{
	object->GetTransform().Translation.x = m_HorizontalBounds.y - object->GetBoxComponent()->GetHalfSize().x;
}

void DJGameMode::TeleportToLeftWall(std::shared_ptr<GameObject> object)
{
	object->GetTransform().Translation.x = m_HorizontalBounds.x + object->GetBoxComponent()->GetHalfSize().x;
}


void DJGameMode::RespawnPlayer()
{
	Math::Vector spawnPoint = { m_PlatformSpawner->GetLowestVisiblePlatformLocation(), 0 };
	spawnPoint.y += +m_Player->GetBoxComponent()->GetHalfSize().y + 1;

	m_Doodle->SetLocation(spawnPoint);
	m_Doodle->EnableCollision();
	m_Doodle->EnableInput();
}

void DJGameMode::SpawnEnemy()
{
	Math::Vector2D spawnLocation = m_PlatformSpawner->GetLastSetPlatformLocation();
	std::shared_ptr<Monster> enemy = GetScene()->SpawnGameObject<Monster>();
	spawnLocation.y += enemy->GetBoxComponent()->GetHalfSize().y + 0.6;
	enemy->SetLocation({ spawnLocation, 0 });
}

void DJGameMode::SpawnAbility()
{
	Math::Vector2D spawnLocation = m_PlatformSpawner->GetLastSetPlatformLocation();
	std::shared_ptr<ImmunityAbility> ability = GetScene()->SpawnGameObject<ImmunityAbility>();
	spawnLocation.y += ability->GetBoxComponent()->GetHalfSize().y + 0.6;
	ability->SetLocation({ spawnLocation, 0 });
}

void DJGameMode::SpawnWall(std::shared_ptr<GameObject>& object, const std::string& tag)
{
	object = GetScene()->SpawnGameObject<GameObject>();
	object->SetTag(tag);
	object->GetBoxComponent()->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Overlap);
	object->GetBoxComponent()->SetCollisionResponce(ECollisionChannel::WorldStatic, ECollisionResponse::Ignore);
}

void DJGameMode::KillDoodle()
{
	m_Doodle->DisablePhysicsCollision();
	m_Doodle->DisableInput();
}

void DJGameMode::GameOver()
{
	showCursor(true);
	GetWorld()->OpenScene<MenuScene>();
}

void DJGameMode::StartGame()
{
	showCursor(false);

	// Spawn Player
	m_Player = GetScene()->SpawnGameObject<Doodle>();
	m_Doodle = static_pointer_cast<Doodle>(m_Player);

	// Camera
	m_Camera = GetScene()->GetRenderCamera();
	int32_t visibleHorizontalSize;
	if (m_Camera->GetAspectRatio() >= m_MinAspectRatio)
		visibleHorizontalSize = (int32_t)m_MaxViewArea.x;
	else
		visibleHorizontalSize = (int32_t)(m_MinAspectRatio / m_Camera->GetAspectRatio() * m_MaxViewArea.x);

	m_Camera->SetProjection(visibleHorizontalSize);

	Math::Vector2D camBounds = m_Camera->GetCameraBounds();
	m_ViewArea = { std::min(m_MaxViewArea.x, camBounds.x), std::min(m_MaxViewArea.y, camBounds.y) };
	m_Camera->GetTransform().Translation.y = camBounds.y * 0.5 - 4;
	m_HorizontalBounds = { m_Camera->GetTransform().Translation.x - m_ViewArea.x * 0.5, m_Camera->GetTransform().Translation.x + m_ViewArea.x * 0.5 };

	// Spawn Background
	// TODO: Create Childclass LevelBackground and MenuBackground
	for (int i = 0, offset = 72; i < 3; i++)
	{
		double bgY = (i - 1) * offset;
		std::shared_ptr<Background> background = GetScene()->SpawnGameObject<LevelBackground>();
		background->GetSprite()->GetTransform().Scale = { 134.44, (double)offset, 1 };
		background->GetSprite()->GetTransform().Translation = { 4.5, bgY, -1 };
	}

	// Spawn Platform Spawner
	m_PlatformSpawner = GetScene()->SpawnGameObject<PlatformSpawner>();
	m_PlatformSpawner->SetDefaultPlatformPoolSize(36);
	m_PlatformSpawner->SetFakePlatformPoolSize(10);
	m_PlatformSpawner->SpawnPools();

	// Walls
	SpawnWall(m_RightWall, "right wall");
	SpawnWall(m_LeftWall, "left wall");
	SpawnWall(m_Floor, "floor");




	double wallWidth = 2;

	// Walls
	m_RightWall->GetBoxComponent()->SetHalfSize({ wallWidth, m_ViewArea.y * 0.5 });
	m_RightWall->SetLocation({ m_HorizontalBounds.y + wallWidth + m_Player->GetBoxComponent()->GetHalfSize().x + 0.5, 0 });
	m_LeftWall->GetBoxComponent()->SetHalfSize({ wallWidth, m_ViewArea.y * 0.5 });
	m_LeftWall->SetLocation({ m_HorizontalBounds.x - wallWidth - m_Player->GetBoxComponent()->GetHalfSize().x - 0.5, 0 });
	m_Floor->GetBoxComponent()->SetHalfSize({ m_ViewArea.x, wallWidth });
	m_Floor->SetLocation({ 0, -m_ViewArea.y * 0.5 - wallWidth });

	m_PlatformSpawner->RestartSpawner();
	for (int i = 0; i < 36; i++)
		m_PlatformSpawner->SetNextPlatform(1);

	RespawnPlayer();

	m_DistanceScore = 0;
	m_PlatformScore = 0;
	m_PlayerLifes = 0;

	double widgetY = m_ViewArea.y / 2 - 1.5;

	m_DistanceScoreWidget = GetScene()->SpawnGameObject<NumberWidget>();
	m_DistanceScoreWidget->SetCoordinates({ -16.5, widgetY });
	m_DistanceScoreWidget->Init(6);
	m_DistanceScoreWidget->Start();

	m_PlatformScoreWidget = GetScene()->SpawnGameObject<NumberWidget>();
	m_PlatformScoreWidget->SetCoordinates({ 6, widgetY });
	m_PlatformScoreWidget->Init(5);
	m_PlatformScoreWidget->Start();

	m_LifesWidget = GetScene()->SpawnGameObject<NumberWidget>();
	m_LifesWidget->SetCoordinates({ 0, widgetY });
	m_LifesWidget->Init(1);
	m_LifesWidget->Start();

	CreateWidget("S_UnderwaterTop", { 0, widgetY }, { camBounds.x, 4.106 }, 1);
	CreateWidget("S_Bamboo", { 15, widgetY }, { 4, 1.08 }, 2);
	CreateWidget("S_Heart", { 2, widgetY }, { 2, 2 }, 2);
	CreateWidget("S_DistanceIcon", { -7, widgetY }, { 2, 2 }, 2);
	CreateWidget("S_UnderwaterLight", { 0, widgetY - 18 }, { camBounds.x, 35.3 }, -0.6);
	CreateWidget("S_BlackBar", { -68, 0 }, { 100, 200 }, 2);
	CreateWidget("S_BlackBar", { 68, 0 }, { 100, 200 }, 2);
	CreateWidget("S_BlackBar", { 0, 104 }, { 100, 100 }, 2);
	CreateWidget("S_BlackBar", { 0, -104 }, { 100, 100 }, 2);

}

