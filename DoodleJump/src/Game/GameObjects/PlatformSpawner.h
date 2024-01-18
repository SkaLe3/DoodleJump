#pragma once
#include "Entities/GameObject.h"
#include "Framework.h"

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

	void SetNextPlatform();

public:

private:

	double lastDefaultPlatformLocation = 0;



	std::shared_ptr<Sprite> defaultPlatformSprite;
	
	uint32_t defaultPlatformPoolSize;
	std::vector<std::shared_ptr<Platform>> defaultPlatformPool;

	std::shared_ptr<CameraComponent> camera;
};