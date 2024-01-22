#pragma once
#include "Entities/GameMode.h"
#include "Math/Vector2D.h"
#include <memory>
#include <random>

class CameraComponent;
class PlatformSpawner;

class DJGameMode : public GameMode
{
public:
	DJGameMode();

	virtual void Start() override;
	virtual void Tick(double DeltaTime) override;

public:
	void TeleportToRightWall(std::shared_ptr<GameObject> object);
	void TeleportToLeftWall(std::shared_ptr<GameObject> object);


	void RespawnPlayer();
	void SpawnEnemy();
	void SpawnAbility();

	void KillDoodle();
	void GameOver();
	void StartGame();


private:

	bool gameStarted = false;
	double distanceScore = 0;
	int platformScore = 0;

	Math::Vector2D horizontalBounds;

	std::shared_ptr<CameraComponent> camera;

	std::shared_ptr<PlatformSpawner> platformSpawner;

	std::shared_ptr<GameObject> rightWall;
	std::shared_ptr<GameObject> leftWall;
	std::shared_ptr<GameObject> floor;

	std::random_device rd;
	std::default_random_engine gen{ rd() };
	
	double enemySpawnProbability = 0.05;
	double abilitySpawnFrequency = 50;
	std::bernoulli_distribution enemySpawnDistribution{ enemySpawnProbability };
};