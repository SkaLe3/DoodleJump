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
#include "GameObjects/Monster.h"

DJGameMode::DJGameMode()
{
	// Player
	player = GetScene()->SpawnGameObject<Doodle>();


	// Background
	std::shared_ptr<GameObject> background = GetScene()->SpawnGameObject<Background>();

	platformSpawner = GetScene()->SpawnGameObject<PlatformSpawner>();
	platformSpawner->SetDefaultPlatformPoolSize(36);

	rightWall = GetScene()->SpawnGameObject<GameObject>();
	rightWall->SetTag("right wall");
	leftWall = GetScene()->SpawnGameObject<GameObject>();
	leftWall->SetTag("left wall");
	floor = GetScene()->SpawnGameObject<GameObject>();
	floor->SetTag("floor");

}

void DJGameMode::Start()
{
	GameMode::Start();

	showCursor(false);
	camera = GetScene()->GetRenderCamera();
	Math::Vector2D camBounds = camera->GetCameraBounds();
	camera->GetTransform().Translation.y = camBounds.y * 0.5 - 4;
	horizontalBounds = { camera->GetTransform().Translation.x - camBounds.x * 0.5, camera->GetTransform().Translation.x + camBounds.x * 0.5 };



	double wallWidth = 2;

	rightWall->GetBoxComponent()->SetHalfSize({ wallWidth, camBounds.y * 0.5 });
	leftWall->GetBoxComponent()->SetHalfSize({ wallWidth, camBounds.y * 0.5 });
	floor->GetBoxComponent()->SetHalfSize({ camBounds.x, wallWidth });
	rightWall->SetLocation({ horizontalBounds.y + wallWidth + player->GetBoxComponent()->GetHalfSize().x + 0.5, 0 });
	leftWall->SetLocation({ horizontalBounds.x - wallWidth - player->GetBoxComponent()->GetHalfSize().x - 0.5, 0});
	floor->SetLocation({ 0, -camBounds.y * 0.5 - wallWidth });

	rightWall->GetBoxComponent()->SetCollisionResponce(ECollisionChannel::Character, ECollisionResponse::Overlap);
	rightWall->GetBoxComponent()->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Overlap);
	leftWall->GetBoxComponent()->SetCollisionResponce(ECollisionChannel::Character, ECollisionResponse::Overlap);
	leftWall->GetBoxComponent()->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Overlap);
	floor->GetBoxComponent()->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Ignore);
	floor->GetBoxComponent()->SetCollisionResponce(ECollisionChannel::WorldStatic, ECollisionResponse::Ignore);

	platformSpawner->SpawnPools();

	StartGame();
	
}

void DJGameMode::Tick(double DeltaTime)
{
	GameMode::Tick(DeltaTime);
	//if (!gameStarted)
		//return;
	Math::Vector2D camBounds = camera->GetCameraBounds();
	Math::Vector camPos = camera->GetTransform().Translation;
	rightWall->GetBoxComponent()->GetTransform().Translation.y = camPos.y;
	leftWall->GetBoxComponent()->GetTransform().Translation.y = camPos.y;
	floor->GetBoxComponent()->GetTransform().Translation.y = camPos.y - 2 - camBounds.y * 0.5;

	distanceScore = std::max(player->GetLocation().y, distanceScore);

	//std::cout << (int)distanceScore << std::endl;
	//std::cout << "FPS: " << 1.0 / DeltaTime << std::endl;

	bool platformSet = platformSpawner->SetNextPlatform(distanceScore);

	if (platformSet && enemySpawnDistribution(gen))
		SpawnEnemy();
}

void DJGameMode::TeleportToRightWall(std::shared_ptr<GameObject> object)
{
	object->GetTransform().Translation.x = horizontalBounds.y - object->GetBoxComponent()->GetHalfSize().x;
}

void DJGameMode::TeleportToLeftWall(std::shared_ptr<GameObject> object)
{
	object->GetTransform().Translation.x = horizontalBounds.x + object->GetBoxComponent()->GetHalfSize().x;
}

void DJGameMode::SpawnEnemy()
{
	Math::Vector2D spawnLocation =  platformSpawner->GetLastSetPlatformLocation();
	std::shared_ptr<Monster> enemy = GetScene()->SpawnGameObject<Monster>();
	spawnLocation.y += enemy->GetBoxComponent()->GetHalfSize().y + 0.6;
	enemy->SetLocation({ spawnLocation, 0 });
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
	StartGame();

}

void DJGameMode::StartGame()
{
	showCursor(false);
	gameStarted = true;
	std::shared_ptr<Doodle> doodle = static_pointer_cast<Doodle>(player);
	doodle->EnableCollision();
	doodle->EnableInput();
	Math::Vector2D camBounds = camera->GetCameraBounds();
	camera->GetTransform().Translation.y = camBounds.y * 0.5 - 4;
	Math::Vector camPos = camera->GetTransform().Translation;
	player->GetTransform().Translation.y = camPos.y - camBounds.y * 0.5 + 4;
	player->GetTransform().Translation.z = 1;
	player->GetTransform().Translation.x = 0;
	//floor->GetBoxComponent()->GetTransform().Translation.y = camPos.y - 2 - camBounds.y * 0.5;
	floor->SetLocation({ 0, -camBounds.y * 0.5 - 2 });
	platformSpawner->RestartSpawner();
	for (int i = 0; i < 36; i++)
		platformSpawner->SetNextPlatform(1);

	distanceScore = 0;

}
