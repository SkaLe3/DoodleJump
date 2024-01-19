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




	




}

void DJGameMode::Start()
{
	GameMode::Start();

	showCursor(false);
	camera = GetScene()->GetRenderCamera();
	Math::Vector2D camBounds = camera->GetCameraBounds();
	horizontalBounds = { camera->GetTransform().Translation.x - camBounds.x * 0.5, camera->GetTransform().Translation.x + camBounds.x * 0.5 };
	camera->GetTransform().Translation.y = camBounds.y * 0.5 - 4;
	Math::Vector camPos = camera->GetTransform().Translation;

	player->GetTransform().Translation.y = camPos.y - camBounds.y * 0.5 + 4;
	player->GetTransform().Translation.z = 1;

	double wallWidth = 2;

	rightWall->GetBoxComponent()->SetHalfSize({ wallWidth, camBounds.y * 0.5 });
	leftWall->GetBoxComponent()->SetHalfSize({ wallWidth, camBounds.y * 0.5 });
	rightWall->SetLocation({ horizontalBounds.y + wallWidth + player->GetBoxComponent()->GetHalfSize().x + 0.5, 0 });
	leftWall->SetLocation({ horizontalBounds.x - wallWidth - player->GetBoxComponent()->GetHalfSize().x - 0.5, 0});

	rightWall->GetBoxComponent()->SetCollisionResponce(ECollisionChannel::Character, ECollisionResponse::Overlap);
	rightWall->GetBoxComponent()->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Ignore);
	leftWall->GetBoxComponent()->SetCollisionResponce(ECollisionChannel::Character, ECollisionResponse::Overlap);
	leftWall->GetBoxComponent()->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Ignore);

	platformSpawner->SpawnPools();

	for (int i = 0; i < 36; i++)
		platformSpawner->SetNextPlatform(1);
	
}

void DJGameMode::Tick(double DeltaTime)
{
	GameMode::Tick(DeltaTime);

	Math::Vector camPos = camera->GetTransform().Translation;
	rightWall->GetBoxComponent()->GetTransform().Translation.y = camPos.y;
	leftWall->GetBoxComponent()->GetTransform().Translation.y = camPos.y;

	distanceScore = std::max(player->GetLocation().y, distanceScore);

	std::cout << (int)distanceScore << std::endl;

	platformSpawner->SetNextPlatform(distanceScore);
}

void DJGameMode::TeleportToRightWall()
{
	player->GetTransform().Translation.x = horizontalBounds.y - player->GetBoxComponent()->GetHalfSize().x;
}

void DJGameMode::TeleportToLeftWall()
{
	player->GetTransform().Translation.x = horizontalBounds.x + player->GetBoxComponent()->GetHalfSize().x;
}
