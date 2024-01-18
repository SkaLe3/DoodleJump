#include "PlatformSpawner.h"
#include "GameObjects/Platform.h"
#include "Math/MyMath.h"

#include <algorithm>
// debug
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
	std::shared_ptr<Platform> platform = defaultPlatformPool.front();
	defaultPlatformPool.pop_front();
	platform->GetBoxComponent()->GetTransform().Translation = Math::Vector{ 0,camera->GetTransform().Translation.y - camera->GetCameraBounds().y * 0.5, -0.5 };
	defaultPlatformPool.push_back(platform);
	lastPlacedPlatform = platform;

	platformDistanceDistribution.param(std::uniform_real_distribution<double>::param_type(1, maxPlatformDistance));
	double horizontalRange = camera->GetCameraBounds().x * 0.5 - defaultPlatformPool.front()->GetBoxComponent()->GetHalfSize().x;
	platformHorizontalRangeDistribution.param(std::uniform_real_distribution<double>::param_type(-horizontalRange, horizontalRange));

}

void PlatformSpawner::SetDefaultPlatformPoolSize(uint32_t size)
{
	defaultPlatformPoolSize = size;
}

void PlatformSpawner::SetNextPlatform(double score)
{
	std::shared_ptr<Platform> lastPlatform = defaultPlatformPool.front();
	if (lastPlatform->GetLocation().y + 2 > camera->GetTransform().Translation.y - camera->GetCameraBounds().y * 0.5)
		return;

	double minDistance = score / 1000 * (10 - 2); // Interpolate
	double maxDistance = score / 1000 * (maxPlatformDistance - 6);
	maxDistance = std::clamp<double>(maxDistance, 0, maxPlatformDistance - 6);
	minDistance = std::clamp<double>(minDistance, 0, 10-2);


	platformDistanceDistribution.param(std::uniform_real_distribution<double>::param_type(minDistance + 2, maxDistance + 6));


	double distance =  platformDistanceDistribution(gen);
	double horizontalLocation = platformHorizontalRangeDistribution(gen);


	double lppy = lastPlacedPlatform->GetLocation().y;
	lastPlatform->SetLocation({ horizontalLocation, distance + lppy, 0 });
	lastPlacedPlatform = lastPlatform;

	defaultPlatformPool.pop_front();
	defaultPlatformPool.push_back(lastPlatform);
}
