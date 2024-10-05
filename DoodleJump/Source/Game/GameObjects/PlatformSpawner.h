#pragma once
#include "Core/Entities/GameObject.h"

#include <random>
#include <list>

class Platform;
class CameraComponent;

class PlatformSpawner : public GameObject
{
public:
	PlatformSpawner();
	~PlatformSpawner();

	//~ Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	//~ End Object Interface

	void RestartSpawner();
	void SpawnPools();

	void SetDefaultPlatformPoolSize(uint32_t size);
	void SetFakePlatformPoolSize(uint32_t size);
	bool SetNextPlatform(double score);

	void MoveLastSetPlatform();
	Math::Vector2D GetLastSetPlatformLocation();
	Math::Vector2D GetLowestVisiblePlatformLocation();
	int32_t GetPassedPlatformCount();
	void StopLastSetPlatform();

private:
	std::shared_ptr<Platform> m_LastPlacedPlatform;
	std::list<std::shared_ptr<Platform>> m_DefaultPlatformPool;
	std::list<std::shared_ptr<Platform>> m_FakePlatformPool;

	std::random_device m_RandomDevice;
	std::default_random_engine m_RandomEngine{ m_RandomDevice() };
	std::uniform_real_distribution<double> m_PlatformDistanceDistribution;
	std::uniform_real_distribution<double> m_PlatformHorizontalRangeDistribution;
	double m_BaseMovingProbability = 0.1;

	std::shared_ptr<MySprite> m_DefaultPlatformSprite;
	
	std::shared_ptr<CameraComponent> m_Camera;
	std::shared_ptr<GameObject> m_Player;

	double m_LastDefaultPlatformLocation = 0;
	double m_MaxPlatformDistance = 17;
	int32_t m_PlatformPassed = 0;
	uint32_t m_DefaultPlatformPoolSize;
	uint32_t m_FakePlatformPoolSize;
};