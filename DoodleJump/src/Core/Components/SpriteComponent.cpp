#include "SpriteComponent.h"
#include "World/World.h"
#include "World/Scene.h"

SpriteComponent::~SpriteComponent()
{

}

void SpriteComponent::Destroy()
{
	GetScene()->DestroyDrawObject(GetScene()->GetComponent(this));
}
