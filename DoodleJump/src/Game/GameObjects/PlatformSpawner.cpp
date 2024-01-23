#include "PlatformSpawner.h"
#include "GameObjects/Platform.h"
#include "GameObjects/FakePlatform.h"
#include "GameModes/DJGameMode.h"
#include "Components/CameraComponent.h"
#include "Math/MyMath.h"

#include <algorithm>
#include <utility>


PlatformSpawner::PlatformSpawner() : GameObject(), defaultPlatformPoolSize(10)
{
	std::shared_ptr<MySprite> defaultPlatformRef = std::make_shared<MySprite>("assets/platform.png");
	defaultPlatformSprite = defaultPlatformRef;

	fakePlatformAnimation = std::make_shared<AnimationMachine>();
	std::shared_ptr<std::vector<std::shared_ptr<MySprite>>> animStateBreak = std::make_shared<std::vector<std::shared_ptr<MySprite>>>();
	animStateBreak->emplace_back(std::make_shared<MySprite>("assets/fake-platform-1.png"));
	animStateBreak->emplace_back(std::make_shared<MySprite>("assets/fake-platform-2.png"));
	animStateBreak->emplace_back(std::make_shared<MySprite>("assets/fake-platform-3.png"));
	animStateBreak->emplace_back(std::make_shared<MySprite>("assets/fake-platform-4.png"));

	std::shared_ptr<std::vector<std::shared_ptr<MySprite>>> animStateIdle = std::make_shared<std::vector<std::shared_ptr<MySprite>>>();
	animStateIdle->emplace_back(std::make_shared<MySprite>("assets/fake-platform-1.png"));

	(*fakePlatformAnimation)["break"] = std::make_pair(animStateBreak, 0.08);
	(*fakePlatformAnimation)["idle"] = std::make_pair(animStateIdle, 0);
}

void PlatformSpawner::Start()
{
	GameObject::Start();
	boxComponent->SetCollisionEnabled(false);

	player = GetScene()->GetGameMode()->GetPlayer();


}

void PlatformSpawner::Tick(double DeltaTime)
{
	GameObject::Tick(DeltaTime);

	double location = player->GetTransform().Translation.y;

	for (auto& platform : defaultPlatformPool)
	{
		if (location < platform->GetLocation().y)
			break;
		if (!platform->IsPassed())
		{
			platform->Pass();
			platformPassed++;
		}
	
	}
	for (auto& platform : fakePlatformPool)
	{
		if (location < platform->GetLocation().y)
			break;
		if (!platform->IsPassed())
		{
			platform->Pass();
			platformPassed++;
		}

	}

}

void PlatformSpawner::RestartSpawner()
{
	for (auto& platform : defaultPlatformPool)
	{
		platform->GetTransform().Translation = { -40, -40, -0.5 };

	}
	for (auto& platform : fakePlatformPool)
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
	for (int i = 0; i < fakePlatformPoolSize; i++)
	{
		std::shared_ptr<Platform> platform = GetScene()->SpawnGameObject<FakePlatform>();
		fakePlatformPool.push_back(platform);
		platform->GetSpriteComponent()->SetAnimationMachine(fakePlatformAnimation);
		platform->GetSpriteComponent()->EnableAnimation();
		platform->GetSpriteComponent()->SwitchAnimationState("idle");
		platform->SetTag("fake platform");
	}

	platformDistanceDistribution.param(std::uniform_real_distribution<double>::param_type(1, maxPlatformDistance));
	double horizontalRange = camera->GetCameraBounds().x * 0.5 - defaultPlatformPool.front()->GetBoxComponent()->GetHalfSize().x;
	platformHorizontalRangeDistribution.param(std::uniform_real_distribution<double>::param_type(-horizontalRange, horizontalRange));

}

void PlatformSpawner::SetDefaultPlatformPoolSize(uint32_t size)
{
	defaultPlatformPoolSize = size;
}

void PlatformSpawner::SetFakePlatformPoolSize(uint32_t size)
{
	fakePlatformPoolSize = size;
}

bool PlatformSpawner::SetNextPlatform(double score)
{
	std::shared_ptr<Platform> lastPlatform = defaultPlatformPool.front();
	if (lastPlatform->GetLocation().y + 0.1 > camera->GetTransform().Translation.y - camera->GetCameraBounds().y * 0.5)
		return false;

	double minDistance = score / 25000 * (8 - 2); // Interpolate
	double maxDistance = score / 15000 * (maxPlatformDistance - 6);
	minDistance = std::clamp<double>(minDistance, 0, 8-2);
	maxDistance = std::clamp<double>(maxDistance, 0, maxPlatformDistance - 6);


	platformDistanceDistribution.param(std::uniform_real_distribution<double>::param_type(minDistance + 2, maxDistance + 6));


	double distance =  platformDistanceDistribution(gen);
	double horizontalLocation = platformHorizontalRangeDistribution(gen);


	double lppy = lastPlacedPlatform->GetLocation().y;
	lastPlatform->SetLocation({ horizontalLocation, distance + lppy, 0 });
	lastPlacedPlatform = lastPlatform;
	lastPlatform->Reset();

	defaultPlatformPool.pop_front();
	defaultPlatformPool.push_back(lastPlatform);

	// Fake platform
	lastPlatform = fakePlatformPool.front();
	if (lastPlatform->GetLocation().y + 2 > camera->GetTransform().Translation.y - camera->GetCameraBounds().y * 0.5)
		return true;

	distance = platformDistanceDistribution(gen);
	horizontalLocation = platformHorizontalRangeDistribution(gen);

	lastPlatform->SetLocation({ horizontalLocation, distance * 20 + camera->GetTransform().Translation.y, 0 });
	lastPlatform->Reset();

	fakePlatformPool.pop_front();
	fakePlatformPool.push_back(lastPlatform);

	return true;
}

Math::Vector2D PlatformSpawner::GetLastSetPlatformLocation()
{
	return defaultPlatformPool.back()->GetLocation();
}

Math::Vector2D PlatformSpawner::GetLowestPlatformLocation()
{
	return defaultPlatformPool.front()->GetLocation();
}

int32_t PlatformSpawner::GetPassedPlatformCount()
{
	return platformPassed;
}
