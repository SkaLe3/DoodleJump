#include "SpriteComponent.h"
#include "World/World.h"
#include "World/Scene.h"

void SpriteComponent::Destroy()
{
	GetScene()->DestroyDrawObject(GetScene()->GetComponent(this));
}
