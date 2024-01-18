#pragma once
#include "Entities/GameMode.h"
#include <memory>

class CameraComponent;
class PlatformSpawner;

class DJGameMode : public GameMode
{
public:
	DJGameMode();

	virtual void Start() override;
	virtual void Tick(double DeltaTime) override;

private:

	double score = 0;

	std::shared_ptr<CameraComponent> camera;

	std::shared_ptr<PlatformSpawner> platformSpawner;

	std::shared_ptr<GameObject> rightWall;
	std::shared_ptr<GameObject> leftWall;
};