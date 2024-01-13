#include "World.h"

void World::Update()
{
	currentScene->Tick(DeltaTime);
}
