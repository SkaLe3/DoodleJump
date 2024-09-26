#include "PlatformSpawner.h"
#include "GameObjects/Platform.h"
#include "GameObjects/FakePlatform.h"
#include "GameModes/DJGameMode.h"
#include "Components/CameraComponent.h"
#include "Math/MyMath.h"

#include <algorithm>
#include <utility>
#include "Core/Base/Log.h"

PlatformSpawner::PlatformSpawner() : GameObject(), m_DefaultPlatformPoolSize(10)
{
	std::shared_ptr<MySprite> defaultPlatformRef = std::make_shared<MySprite>("assets2/platform.png");
	m_DefaultPlatformSprite = defaultPlatformRef;

	OBJECT_LOG_CONSTRUCTOR()
}


PlatformSpawner::~PlatformSpawner()
{
	OBJECT_LOG_DESTRUCTOR()
}

void PlatformSpawner::Start()
{
	GameObject::Start();
	m_BoxComponent->SetCollisionEnabled(false);

	m_Player = GetScene()->GetGameMode()->GetPlayer();
}

void PlatformSpawner::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);

	double location = m_Player->GetTransform().Translation.y;

	for (auto& platform : m_DefaultPlatformPool)
	{
		if (location < platform->GetLocation().y)
			break;
		if (!platform->IsPassed())
		{
			platform->Pass();
			m_PlatformPassed++;
		}
	}
	for (auto& platform : m_FakePlatformPool)
	{
		if (location < platform->GetLocation().y)
			break;
		if (!platform->IsPassed())
		{
			platform->Pass();
			m_PlatformPassed++;
		}
	}
}

void PlatformSpawner::RestartSpawner()
{
	for (auto& platform : m_DefaultPlatformPool)
	{
		platform->GetTransform().Translation = { -40, -40, -0.5 };

	}
	for (auto& platform : m_FakePlatformPool)
	{
		platform->GetTransform().Translation = { -40, -40, -0.5 };

	}
	std::shared_ptr<Platform> platform = m_DefaultPlatformPool.front();
	m_DefaultPlatformPool.pop_front();
	platform->GetBoxComponent()->GetTransform().Translation = Math::Vector{ 0,m_Camera->GetTransform().Translation.y - m_Camera->GetCameraBounds().y * 0.5, -0.5 };
	m_DefaultPlatformPool.push_back(platform);
	m_LastPlacedPlatform = platform;
}

void PlatformSpawner::SpawnPools()
{
	m_Camera = GetScene()->GetRenderCamera();

	for (uint32_t i = 0; i < m_DefaultPlatformPoolSize; i++)
	{
		std::shared_ptr<Platform> platform = GetScene()->SpawnGameObject<Platform>();
		m_DefaultPlatformPool.push_back(platform);
		platform->GetSprite()->SetSprite(m_DefaultPlatformSprite);
		platform->SetTag("platform");

	}
	for (uint32_t i = 0; i < m_FakePlatformPoolSize; i++)
	{
		std::shared_ptr<Platform> platform = GetScene()->SpawnGameObject<FakePlatform>();
		m_FakePlatformPool.push_back(platform);
		platform->SetTag("fake platform");
	}

	m_PlatformDistanceDistribution.param(std::uniform_real_distribution<double>::param_type(1, m_MaxPlatformDistance));
	double horizontalRange = m_Camera->GetCameraBounds().x * 0.5 - m_DefaultPlatformPool.front()->GetBoxComponent()->GetHalfSize().x;
	m_PlatformHorizontalRangeDistribution.param(std::uniform_real_distribution<double>::param_type(-horizontalRange, horizontalRange));

}

void PlatformSpawner::SetDefaultPlatformPoolSize(uint32_t size)
{
	m_DefaultPlatformPoolSize = size;
}

void PlatformSpawner::SetFakePlatformPoolSize(uint32_t size)
{
	m_FakePlatformPoolSize = size;
}

bool PlatformSpawner::SetNextPlatform(double score)
{
	std::shared_ptr<Platform> lastPlatform = m_DefaultPlatformPool.front();
	if (lastPlatform->GetLocation().y + 0.1 > m_Camera->GetTransform().Translation.y - m_Camera->GetCameraBounds().y * 0.5)
		return false;

	double minDistance = score / 25000 * (8 - 2); // Interpolate
	double maxDistance = score / 15000 * (m_MaxPlatformDistance - 6);
	minDistance = std::clamp<double>(minDistance, 0, 8 - 2);
	maxDistance = std::clamp<double>(maxDistance, 0, m_MaxPlatformDistance - 6);


	m_PlatformDistanceDistribution.param(std::uniform_real_distribution<double>::param_type(minDistance + 2, maxDistance + 6));


	double distance = m_PlatformDistanceDistribution(m_RandomEngine);
	double horizontalLocation = m_PlatformHorizontalRangeDistribution(m_RandomEngine);


	double lppy = m_LastPlacedPlatform->GetLocation().y;
	lastPlatform->SetLocation({ horizontalLocation, distance + lppy, 0 });
	m_LastPlacedPlatform = lastPlatform;
	lastPlatform->Reset();

	m_DefaultPlatformPool.pop_front();
	m_DefaultPlatformPool.push_back(lastPlatform);

	// Fake platform
	lastPlatform = m_FakePlatformPool.front();
	if (lastPlatform->GetLocation().y + 2 > m_Camera->GetTransform().Translation.y - m_Camera->GetCameraBounds().y * 0.5)
		return true;

	distance = m_PlatformDistanceDistribution(m_RandomEngine);
	horizontalLocation = m_PlatformHorizontalRangeDistribution(m_RandomEngine);

	lastPlatform->SetLocation({ horizontalLocation, distance * 20 + m_Camera->GetTransform().Translation.y, 0 });
	lastPlatform->Reset();

	m_FakePlatformPool.pop_front();
	m_FakePlatformPool.push_back(lastPlatform);

	return true;
}

Math::Vector2D PlatformSpawner::GetLastSetPlatformLocation()
{
	return m_DefaultPlatformPool.back()->GetLocation();
}

Math::Vector2D PlatformSpawner::GetLowestPlatformLocation()
{
	return m_DefaultPlatformPool.front()->GetLocation();
}

int32_t PlatformSpawner::GetPassedPlatformCount()
{
	return m_PlatformPassed;
}
