#pragma once
#include "Entities/GameMode.h"
#include "Math/Vector2D.h"
#include <memory>
#include <random>

class CameraComponent;
class PlatformSpawner;
class NumberWidget;
class SpriteWidget;
class Doodle;

class DJGameMode : public GameMode
{
public:
	DJGameMode();

	virtual void Start() override;
	virtual void Tick(double DeltaTime) override;
	virtual void Destroy() override;

public:
	void UpdateWidget(std::shared_ptr<NumberWidget> widget, int32_t& value, int32_t newValue);
	void CreateWidget(const std::string& path, Math::Vector2D coords, Math::Vector2D scale, double zLocation);

	void TeleportToRightWall(std::shared_ptr<GameObject> object);
	void TeleportToLeftWall(std::shared_ptr<GameObject> object);


	void RespawnPlayer();
	void SpawnEnemy();
	void SpawnAbility();
	void SpawnWall(std::shared_ptr<GameObject>& object, const std::string& tag);

	void KillDoodle();
	void GameOver();
	void StartGame();



private:
	std::shared_ptr<Doodle> doodle;

	bool gameStarted = false;
	int32_t distanceScore = 0;
	int32_t platformScore = 0;
	int32_t playerLifes = 0;

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

	std::shared_ptr<NumberWidget> distanceScoreWidget;
	std::shared_ptr<NumberWidget> platformScoreWidget;
	std::shared_ptr<NumberWidget> lifesWidget;

};