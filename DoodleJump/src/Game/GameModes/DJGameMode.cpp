#include "Framework.h"

#include "DJGameMode.h"
#include "GameObjects/Doodle.h"
#include "Background.h"
#include "GameObjects/PlatformSpawner.h"
#include "Components/CameraComponent.h"
#include "GameObjects/Monster.h"
#include "GameObjects/Abilities/ImmunityAbility.h"
#include "GameObjects/UI/NumberWidget.h"
#include "Components/UI/NumberComponent.h"
#include "GameObjects/UI/SpriteWidget.h"

DJGameMode::DJGameMode()
{
}

void DJGameMode::Start()
{
	StartGame();
}

void DJGameMode::Tick(double deltaTime)
{
	Math::Vector2D camBounds = camera->GetCameraBounds();
	Math::Vector camPos = camera->GetTransform().Translation;

	rightWall->GetBoxComponent()->GetTransform().Translation.y = camPos.y;
	leftWall->GetBoxComponent()->GetTransform().Translation.y = camPos.y;
	floor->GetBoxComponent()->GetTransform().Translation.y = camPos.y - 2 - camBounds.y * 0.5;

	UpdateWidget(distanceScoreWidget, distanceScore, std::max((int32_t)player->GetLocation().y, distanceScore));
	UpdateWidget(platformScoreWidget, platformScore, platformSpawner->GetPassedPlatformCount());
	UpdateWidget(lifesWidget, playerLifes, doodle->GetLifesCount());

 	bool platformSet = platformSpawner->SetNextPlatform(distanceScore);

	if (platformSet && enemySpawnDistribution(gen))
		SpawnEnemy();

	if (platformSet && doodle->GetJumpsCount() >= abilitySpawnFrequency)
	{
		doodle->ResetJumpsCount();
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

void DJGameMode::CreateWidget(const std::string& path, Math::Vector2D coords, Math::Vector2D scale, double zLocation)
{
	std::shared_ptr<SpriteWidget> sprite = GetScene()->SpawnGameObject<SpriteWidget>();
	sprite->SetCoordinates(coords);
	std::shared_ptr<SpriteComponent> sc = sprite->GetSprite();
	std::shared_ptr<MySprite> spriteRef = std::make_shared<MySprite>(path.c_str());
	sc->SetSprite(spriteRef);
	sc->GetTransform().Scale = { scale, 1 };
	sc->GetTransform().Translation.z = zLocation;
}

void DJGameMode::TeleportToRightWall(std::shared_ptr<GameObject> object)
{
	object->GetTransform().Translation.x = horizontalBounds.y - object->GetBoxComponent()->GetHalfSize().x;
}

void DJGameMode::TeleportToLeftWall(std::shared_ptr<GameObject> object)
{
	object->GetTransform().Translation.x = horizontalBounds.x + object->GetBoxComponent()->GetHalfSize().x;
}


void DJGameMode::RespawnPlayer()
{
	Math::Vector spawnPoint = { platformSpawner->GetLowestPlatformLocation(), 0 };
	spawnPoint.y += + player->GetBoxComponent()->GetHalfSize().y + 1;	

	doodle->SetLocation(spawnPoint);
	doodle->EnableCollision();
	doodle->EnableInput();
}

void DJGameMode::SpawnEnemy()
{
	Math::Vector2D spawnLocation =  platformSpawner->GetLastSetPlatformLocation();
	std::shared_ptr<Monster> enemy = GetScene()->SpawnGameObject<Monster>();
	spawnLocation.y += enemy->GetBoxComponent()->GetHalfSize().y + 0.6;
	enemy->SetLocation({ spawnLocation, 0 });
}

void DJGameMode::SpawnAbility()
{
	Math::Vector2D spawnLocation = platformSpawner->GetLastSetPlatformLocation();
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
	doodle->DisablePhysicsCollision();
	doodle->DisableInput();
}

void DJGameMode::GameOver()
{
	showCursor(true);
	GetScene()->ClearScene();
	camera = nullptr;
	platformSpawner = nullptr;
	rightWall = nullptr;
	leftWall = nullptr;
	floor = nullptr;
	distanceScoreWidget = nullptr;
	platformScoreWidget = nullptr;
	lifesWidget = nullptr;

	StartGame();
}

void DJGameMode::StartGame()
{
	showCursor(false);

	// Spawn Player
	player = GetScene()->SpawnGameObject<Doodle>();
	doodle = static_pointer_cast<Doodle>(player);

	// Spawn Background
	GetScene()->SpawnGameObject<Background>();

	// Spawn Platform Spawner
	platformSpawner = GetScene()->SpawnGameObject<PlatformSpawner>();
	platformSpawner->SetDefaultPlatformPoolSize(36);
	platformSpawner->SetFakePlatformPoolSize(6);
	platformSpawner->SpawnPools();

	// Walls
	SpawnWall(rightWall, "right wall");
	SpawnWall(leftWall, "left wall");
	SpawnWall(floor, "floor");


	// Camera
	camera = GetScene()->GetRenderCamera();
	Math::Vector2D camBounds = camera->GetCameraBounds();
	camera->GetTransform().Translation.y = camBounds.y * 0.5 - 4;
	horizontalBounds = { camera->GetTransform().Translation.x - camBounds.x * 0.5, camera->GetTransform().Translation.x + camBounds.x * 0.5 };

	double wallWidth = 2;

	// Walls
	rightWall->GetBoxComponent()->SetHalfSize({ wallWidth, camBounds.y * 0.5 });
	rightWall->SetLocation({ horizontalBounds.y + wallWidth + player->GetBoxComponent()->GetHalfSize().x + 0.5, 0 });
	leftWall->GetBoxComponent()->SetHalfSize({ wallWidth, camBounds.y * 0.5 });
	leftWall->SetLocation({ horizontalBounds.x - wallWidth - player->GetBoxComponent()->GetHalfSize().x - 0.5, 0 });
	floor->GetBoxComponent()->SetHalfSize({ camBounds.x, wallWidth });
	floor->SetLocation({ 0, -camBounds.y * 0.5 - wallWidth });

	player->SetLocation({ 0, 3, 0 });
	platformSpawner->RestartSpawner();
	for (int i = 0; i < 36; i++)
		platformSpawner->SetNextPlatform(1);

	distanceScore = 0;
	platformScore = 0;
	playerLifes = 0;


	distanceScoreWidget = GetScene()->SpawnGameObject<NumberWidget>();
	distanceScoreWidget->SetCoordinates({ -16.5, 34.5 });
	distanceScoreWidget->Init(6);
	distanceScoreWidget->Start();

	platformScoreWidget = GetScene()->SpawnGameObject<NumberWidget>();
	platformScoreWidget->SetCoordinates({ 6, 34.5 });
	platformScoreWidget->Init(5);
	platformScoreWidget->Start();

	lifesWidget = GetScene()->SpawnGameObject<NumberWidget>();
	lifesWidget->SetCoordinates({ 0, 34.5 });
	lifesWidget->Init(1);
	lifesWidget->Start();

	CreateWidget("assets/top.png", { 0, 34.5 }, { camBounds.x, 4.106 }, 1);
	CreateWidget("assets/platform.png", { 15, 34.5 }, { 4, 1.08 }, 2);
	CreateWidget("assets/heart.png", { 2, 34.5 }, { 2, 2 }, 2);
	CreateWidget("assets/distance_icon.png", { -7, 34.5 }, {2, 2}, 2);
	CreateWidget("assets/underwater-light@2x.png", {0, 18.35}, {camBounds.x, 35.3}, -0.6);

}

