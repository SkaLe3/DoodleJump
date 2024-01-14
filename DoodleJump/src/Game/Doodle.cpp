#include "Doodle.h"
#include "Components/SpriteComponent.h"

Doodle::Doodle() : GameObject()
{
	spriteComponent = CreateComponent<SpriteComponent>();
}
