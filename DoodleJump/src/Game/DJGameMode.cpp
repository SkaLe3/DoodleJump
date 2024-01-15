#include "Framework.h"

#include "DJGameMode.h"
#include "Doodle.h"
#include "World/World.h"
#include "Components/SpriteComponent.h"

DJGameMode::DJGameMode()
{
	player = GetScene()->SpawnGameObject<Doodle>();

	Sprite* sprite = createSprite("assets/blue-lik-left@2x.png");
	setSpriteSize(sprite, 124, 120);
	std::shared_ptr<SpriteComponent> sc = static_pointer_cast<Doodle>(player)->GetSprite();

	sc->SetSprite(sprite);

}
