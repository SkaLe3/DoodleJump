#pragma once
#include "Entities/GameMode.h"
#include "Math/Vector2D.h"
#include <memory>

class CameraComponent;
class PlatformSpawner;

class DJGameMode : public GameMode
{
public:
	DJGameMode();

	virtual void Start() override;
	virtual void Tick(double DeltaTime) override;

public:
	void TeleportToRightWall();
	void TeleportToLeftWall();

private:

	double score = 0;

	Math::Vector2D horizontalBounds;

	std::shared_ptr<CameraComponent> camera;

	std::shared_ptr<PlatformSpawner> platformSpawner;

	std::shared_ptr<GameObject> rightWall;
	std::shared_ptr<GameObject> leftWall;
};