#include "PlatformSpawner.h"
#include "GameObjects/Platform.h"
#include "Math/MyMath.h"

//testing
#include <iostream>

PlatformSpawner::PlatformSpawner() : GameObject(), defaultPlatformPoolSize(10)
{
	Sprite* sprite = createSprite("assets/platform.png");
	std::shared_ptr<Sprite> platformSpriteRef;
	platformSpriteRef.reset(sprite);
	defaultPlatformSprite = platformSpriteRef;
}

void PlatformSpawner::Start()
{
	GameObject::Start();
	boxComponent->SetCollisionEnabled(false);

}

void PlatformSpawner::Tick(double DeltaTime)
{
	GameObject::Tick(DeltaTime);
}

void PlatformSpawner::SpawnPools()
{
	camera = GetScene()->GetRenderCamera();

	for (int i = 0; i < defaultPlatformPoolSize; i++)
	{
		std::shared_ptr<Platform> platform = GetScene()->SpawnGameObject<Platform>();
		defaultPlatformPool.push_back(platform);
		platform->GetSpriteComponent()->SetSprite(defaultPlatformSprite);
		platform->GetTransform().Translation.y = camera->GetTransform().Translation.y - camera->GetCameraBounds().y;
		platform->SetTag("platform");

	}

	defaultPlatformPool.front()->GetBoxComponent()->GetTransform().Translation = Math::Vector{ 0,camera->GetTransform().Translation.y -camera->GetCameraBounds().y * 0.5, -0.5 };
}

void PlatformSpawner::SetDefaultPlatformPoolSize(uint32_t size)
{
	defaultPlatformPoolSize = size;
}

void PlatformSpawner::SetNextPlatform()
{

}
