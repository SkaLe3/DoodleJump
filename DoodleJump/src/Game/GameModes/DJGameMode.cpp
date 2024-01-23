#include "Framework.h"

#include "DJGameMode.h"
#include "GameObjects/Doodle.h"
#include "World/World.h"
#include "Components/SpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Math/Vector2D.h"
#include "GameObjects/Platform.h"
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
	GameMode::Start();
	StartGame();

	
}

void DJGameMode::Tick(double DeltaTime)
{
	GameMode::Tick(DeltaTime);

	Math::Vector2D camBounds = camera->GetCameraBounds();
	Math::Vector camPos = camera->GetTransform().Translation;
	rightWall->GetBoxComponent()->GetTransform().Translation.y = camPos.y;
	leftWall->GetBoxComponent()->GetTransform().Translation.y = camPos.y;
	floor->GetBoxComponent()->GetTransform().Translation.y = camPos.y - 2 - camBounds.y * 0.5;

	int32_t newdistance = std::max((int32_t)player->GetLocation().y , distanceScore);
	if ((int)distanceScore != newdistance)
	{
		distanceScoreWidget->Update(newdistance);
		distanceScore = newdistance;
	}
	int32_t newPlatformCount = platformSpawner->GetPassedPlatformCount();
	if (platformScore != newPlatformCount)
	{
		platformScoreWidget->Update(newPlatformCount);
		platformScore = newPlatformCount;
	}
	int32_t newLifesCount = static_pointer_cast<Doodle>(player)->GetLifesCount();
	if (playerLifes != newLifesCount)
	{
		lifesWidget->Update(newLifesCount);
		playerLifes = newLifesCount;
	}

	//std::cout << "FPS: " << 1.0 / DeltaTime << std::endl;


	bool platformSet = platformSpawner->SetNextPlatform(distanceScore);
	if (platformSet)
		platformScore++;

	if (platformSet && enemySpawnDistribution(gen))
	{
		SpawnEnemy();
	}
	std::shared_ptr<Doodle> doodle = static_pointer_cast<Doodle>(player);
	if (platformSet && doodle->GetJumpsCount() >= abilitySpawnFrequency)
	{
		doodle->ResetJumpsCount();
		SpawnAbility();
	}
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
	Math::Vector2D platformLocation = platformSpawner->GetLowestPlatformLocation();
	Math::Vector spawnPoint;
	spawnPoint.y = platformLocation.y + player->GetBoxComponent()->GetHalfSize().y + 1;	
	spawnPoint.x = platformLocation.x;
	player->SetLocation(spawnPoint);
	std::shared_ptr<Doodle> doodle = static_pointer_cast<Doodle>(player);
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

void DJGameMode::KillDoodle()
{
	std::shared_ptr<Doodle> doodle = static_pointer_cast<Doodle>(player);
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
	// Spawn Background
	std::shared_ptr<GameObject> background = GetScene()->SpawnGameObject<Background>();

	// Spawn Platform Spawner
	platformSpawner = GetScene()->SpawnGameObject<PlatformSpawner>();
	platformSpawner->SetDefaultPlatformPoolSize(36);
	platformSpawner->SetFakePlatformPoolSize(6);
	platformSpawner->SpawnPools();

	// Walls
	rightWall = GetScene()->SpawnGameObject<GameObject>();
	rightWall->SetTag("right wall");
	leftWall = GetScene()->SpawnGameObject<GameObject>();
	leftWall->SetTag("left wall");
	floor = GetScene()->SpawnGameObject<GameObject>();
	floor->SetTag("floor");
	rightWall->GetBoxComponent()->SetCollisionResponce(ECollisionChannel::Character, ECollisionResponse::Overlap);
	rightWall->GetBoxComponent()->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Overlap);
	leftWall->GetBoxComponent()->SetCollisionResponce(ECollisionChannel::Character, ECollisionResponse::Overlap);
	leftWall->GetBoxComponent()->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Overlap);
	floor->GetBoxComponent()->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Ignore);
	floor->GetBoxComponent()->SetCollisionResponce(ECollisionChannel::WorldStatic, ECollisionResponse::Ignore);


	// Camera
	camera = GetScene()->GetRenderCamera();
	Math::Vector2D camBounds = camera->GetCameraBounds();
	camera->GetTransform().Translation.y = camBounds.y * 0.5 - 4;
	horizontalBounds = { camera->GetTransform().Translation.x - camBounds.x * 0.5, camera->GetTransform().Translation.x + camBounds.x * 0.5 };



	double wallWidth = 2;
	// Walls
	rightWall->GetBoxComponent()->SetHalfSize({ wallWidth, camBounds.y * 0.5 });
	leftWall->GetBoxComponent()->SetHalfSize({ wallWidth, camBounds.y * 0.5 });
	floor->GetBoxComponent()->SetHalfSize({ camBounds.x, wallWidth });
	rightWall->SetLocation({ horizontalBounds.y + wallWidth + player->GetBoxComponent()->GetHalfSize().x + 0.5, 0 });
	leftWall->SetLocation({ horizontalBounds.x - wallWidth - player->GetBoxComponent()->GetHalfSize().x - 0.5, 0 });
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

	std::shared_ptr<SpriteWidget> topSprite = GetScene()->SpawnGameObject<SpriteWidget>();
	topSprite->SetCoordinates({ 0, 34.5 });
	std::shared_ptr<SpriteComponent> sc1 = topSprite->GetSpriteComponent();
	std::shared_ptr<MySprite> spriteRef1 = std::make_shared<MySprite>("assets/top.png");
	sc1->SetSprite(spriteRef1);
	sc1->GetTransform().Scale = { camBounds.x, 4.106, 1 };
	sc1->GetTransform().Translation.z = 1;

	std::shared_ptr<SpriteWidget> platformImage = GetScene()->SpawnGameObject<SpriteWidget>();
	platformImage->SetCoordinates({ 15, 34.5 });
	std::shared_ptr<SpriteComponent> sc2 = platformImage->GetSpriteComponent();
	std::shared_ptr<MySprite> spriteRef2 = std::make_shared<MySprite>("assets/platform.png");
	sc2->SetSprite(spriteRef2);
	sc2->GetTransform().Scale = { 4, 1.08, 1 };
	sc2->GetTransform().Translation.z = 2;

	std::shared_ptr<SpriteWidget> heart = GetScene()->SpawnGameObject<SpriteWidget>();
	heart->SetCoordinates({ 2, 34.5 });
	std::shared_ptr<SpriteComponent> sc3 = heart->GetSpriteComponent();
	std::shared_ptr<MySprite> spriteRef3 = std::make_shared<MySprite>("assets/heart.png");
	sc3->SetSprite(spriteRef3);
	sc3->GetTransform().Scale = { 2, 2, 1 };
	sc3->GetTransform().Translation.z = 2;

	std::shared_ptr<SpriteWidget> dist = GetScene()->SpawnGameObject<SpriteWidget>();
	dist->SetCoordinates({ -7, 34.5 });
	std::shared_ptr<SpriteComponent> sc4 = dist->GetSpriteComponent();
	std::shared_ptr<MySprite> spriteRef4 = std::make_shared<MySprite>("assets/distance_icon.png");
	sc4->SetSprite(spriteRef4);
	sc4->GetTransform().Scale = { 2, 2, 1 };
	sc4->GetTransform().Translation.z = 2;

	std::shared_ptr<SpriteWidget> light = GetScene()->SpawnGameObject<SpriteWidget>();
	light->SetCoordinates({ 0, 18.35 });
	std::shared_ptr<SpriteComponent> sc5 = light->GetSpriteComponent();
	std::shared_ptr<MySprite> spriteRef5 = std::make_shared<MySprite>("assets/underwater-light@2x.png");
	sc5->SetSprite(spriteRef5);
	sc5->GetTransform().Scale = { camBounds.x, 35.3, 1 };
	sc5->GetTransform().Translation.z = -0.6;


}
