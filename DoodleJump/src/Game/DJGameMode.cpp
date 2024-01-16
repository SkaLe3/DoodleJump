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
		std::shared_ptr<SpriteComponent> sc = static_pointer_cast<Background>(platform)->GetSpriteComponent();
		std::shared_ptr<Sprite> platformSpriteRef;
		platformSpriteRef.reset(platformSprite);
		sc->SetSprite(platformSpriteRef);
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
