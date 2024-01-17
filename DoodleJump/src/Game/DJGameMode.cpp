#include "Framework.h"

#include "DJGameMode.h"
#include "GameObjects/Doodle.h"
#include "World/World.h"
#include "Components/SpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Math/Vector2D.h"
#include "GameObjects/Platform.h"
#include "Background.h"

DJGameMode::DJGameMode()
{
	player = GetScene()->SpawnGameObject<Doodle>();
	std::shared_ptr<GameObject> background = GetScene()->SpawnGameObject<Background>();
	std::shared_ptr<GameObject> platform = GetScene()->SpawnGameObject<Platform>();
	//std::shared_ptr<GameObject> platform2 = GetScene()->SpawnGameObject<Platform>();
	//std::shared_ptr<GameObject> platform3 = GetScene()->SpawnGameObject<Platform>();
	platform->GetTransform().Translation = { 0, -15, -0.5 };
	//platform2->GetTransform().Translation = { 7, -15, -0.5 };
	//platform3->GetTransform().Translation = { -7, -15, -0.5 };
	

	{
		playerSprite = createSprite("assets/bunny-left@2x.png");
		std::shared_ptr<SpriteComponent> sc = static_pointer_cast<Doodle>(player)->GetSpriteComponent();
		std::shared_ptr<Sprite> spriteRef;
		spriteRef.reset(playerSprite);
		sc->SetSprite(spriteRef);
	}

	{
		Sprite* backgroundSprite = createSprite("assets/bck@2x.png");
		std::shared_ptr<SpriteComponent> sc = static_pointer_cast<Background>(background)->GetSpriteComponent();
		std::shared_ptr<Sprite> bgSpriteRef;
		bgSpriteRef.reset(backgroundSprite);
		sc->SetSprite(bgSpriteRef);
	}

	{
		Sprite* platformSprite = createSprite("assets/platform.png");
		std::shared_ptr<SpriteComponent> sc = static_pointer_cast<Platform>(platform)->GetSpriteComponent();
		std::shared_ptr<Sprite> platformSpriteRef;
		platformSpriteRef.reset(platformSprite);
		sc->SetSprite(platformSpriteRef);
// 		std::shared_ptr<SpriteComponent> sc2 = static_pointer_cast<Platform>(platform2)->GetSpriteComponent();
// 		std::shared_ptr<SpriteComponent> sc3 = static_pointer_cast<Platform>(platform3)->GetSpriteComponent();
// 		sc2->SetSprite(platformSpriteRef);
// 		sc3->SetSprite(platformSpriteRef);
	}

}

void DJGameMode::Start()
{
	GameMode::Start();

	showCursor(false);
}

void DJGameMode::Tick(double DeltaTime)
{


	// Tweaking
}
