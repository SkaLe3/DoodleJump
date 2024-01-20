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

void PlatformSpawner::RestartSpawner()
{
	for (auto& platform : defaultPlatformPool)
	{
		platform->GetTransform().Translation = { -40, -40, -0.5 };

	}
	std::shared_ptr<Platform> platform = defaultPlatformPool.front();
	defaultPlatformPool.pop_front();
	platform->GetBoxComponent()->GetTransform().Translation = Math::Vector{ 0,camera->GetTransform().Translation.y - camera->GetCameraBounds().y * 0.5, -0.5 };
	defaultPlatformPool.push_back(platform);
	lastPlacedPlatform = platform;
}

void PlatformSpawner::SpawnPools()
{
	camera = GetScene()->GetRenderCamera();

	for (int i = 0; i < defaultPlatformPoolSize; i++)
	{
		std::shared_ptr<Platform> platform = GetScene()->SpawnGameObject<Platform>();
		defaultPlatformPool.push_back(platform);
		platform->GetSpriteComponent()->SetSprite(defaultPlatformSprite);
		platform->SetTag("platform");

	}
	platformDistanceDistribution.param(std::uniform_real_distribution<double>::param_type(1, maxPlatformDistance));
	double horizontalRange = camera->GetCameraBounds().x * 0.5 - defaultPlatformPool.front()->GetBoxComponent()->GetHalfSize().x;
	platformHorizontalRangeDistribution.param(std::uniform_real_distribution<double>::param_type(-horizontalRange, horizontalRange));

	RestartSpawner();
}

void PlatformSpawner::SetDefaultPlatformPoolSize(uint32_t size)
{
	defaultPlatformPoolSize = size;
}

bool PlatformSpawner::SetNextPlatform(double score)
{
	std::shared_ptr<Platform> lastPlatform = defaultPlatformPool.front();
	if (lastPlatform->GetLocation().y + 2 > camera->GetTransform().Translation.y - camera->GetCameraBounds().y * 0.5)
		return false;

	double minDistance = score / 4000 * (8 - 2); // Interpolate
	double maxDistance = score / 4000 * (maxPlatformDistance - 6);
	minDistance = std::clamp<double>(minDistance, 0, 8-2);
	maxDistance = std::clamp<double>(maxDistance, 0, maxPlatformDistance - 6);


	platformDistanceDistribution.param(std::uniform_real_distribution<double>::param_type(minDistance + 2, maxDistance + 6));


	double distance =  platformDistanceDistribution(gen);
	double horizontalLocation = platformHorizontalRangeDistribution(gen);


	double lppy = lastPlacedPlatform->GetLocation().y;
	lastPlatform->SetLocation({ horizontalLocation, distance + lppy, 0 });
	lastPlacedPlatform = lastPlatform;

	defaultPlatformPool.pop_front();
	defaultPlatformPool.push_back(lastPlatform);

	return true;
}

Math::Vector2D PlatformSpawner::GetLastSetPlatformLocation()
{
	return defaultPlatformPool.back()->GetLocation();
}
