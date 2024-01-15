#include "Framework.h"

#include "DJGameMode.h"
#include "Doodle.h"
#include "World/World.h"
#include "Components/SpriteComponent.h"
#include "Components/BoxComponent.h"
#include "Math/Vector2D.h"

DJGameMode::DJGameMode()
{
	player = GetScene()->SpawnGameObject<Doodle>();
	sprite = createSprite("assets/bunny-left@2x.png");
	quad = createSprite("assets/Icon@2x.png");

	std::shared_ptr<SpriteComponent> sc = static_pointer_cast<Doodle>(player)->GetSpriteComponent();
	std::shared_ptr<Sprite> spriteRef;
	spriteRef.reset(sprite);
	sc->SetSprite(spriteRef);

}

void DJGameMode::Tick(double DeltaTime)
{


	// Tweaking
#if 0
	static bool flip = true;
	std::shared_ptr<SpriteComponent> sc = static_pointer_cast<Doodle>(player)->GetSpriteComponent();
	std::shared_ptr<BoxComponent> box = player->GetBoxComponent();
	sc->GetTransform().Scale = { 1.9, 1.9, 1.0 };
	if (flip)
	{
		sc->SetSprite(sprite);
		sc->GetTransform().Scale = { 6.9, 6.9, 1.0 };
		sc->GetTransform().Translation = { 0.0, 0.7, 0.0 };
		
	}
	else
	{
		sc->SetSprite(quad);
		Math::Vector2D size = box->GetSize();
		sc->GetTransform().Scale = { size.x, size.y, 1.0 };
		sc->GetTransform().Translation = { 0.0, 0.0, 0.0 };
	}
	flip = !flip;
#endif
}
