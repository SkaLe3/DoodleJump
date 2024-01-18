#pragma once
#include "Entities/GameObject.h"
#include <random>

#include "Framework.h"

#include <list>

class Platform;
class CameraComponent;

class PlatformSpawner : public GameObject
{
public:
	PlatformSpawner();

	virtual void Start() override;
	virtual void Tick(double DeltaTime) override;

	void SpawnPools();

	void SetDefaultPlatformPoolSize(uint32_t size);

	void SetNextPlatform(double score);

public:

private:

	double lastDefaultPlatformLocation = 0;

	double maxPlatformDistance = 17;

	std::shared_ptr<Platform> lastPlacedPlatform;

	std::random_device rd;
	std::default_random_engine gen{ rd() };



	std::uniform_real_distribution<double> platformDistanceDistribution;
	std::uniform_real_distribution<double> platformHorizontalRangeDistribution;


	std::shared_ptr<Sprite> defaultPlatformSprite;
	
	uint32_t defaultPlatformPoolSize;
	std::list<std::shared_ptr<Platform>> defaultPlatformPool;

	std::shared_ptr<CameraComponent> camera;
};