#pragma once
#include "Entities/GameMode.h"

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
	~DJGameMode();

	//~ Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;
	//~ End Object Interface

	void UpdateWidget(std::shared_ptr<NumberWidget> widget, int32_t& value, int32_t newValue);
	void CreateWidget(const std::string& assetName, Math::Vector2D coords, Math::Vector2D scale, double zLocation);

	void TeleportToRightWall(std::weak_ptr<GameObject> object);
	void TeleportToLeftWall(std::weak_ptr<GameObject> object);

	void RespawnPlayer();
	void SpawnEnemy();
	void SpawnAbility();
	void SpawnWall(std::shared_ptr<GameObject>& object, const std::string& tag);

	void KillDoodle();
	void GameOver();
	void StartGame();

private:
	std::shared_ptr<Doodle> m_Doodle;
	std::shared_ptr<CameraComponent> m_Camera;
	std::shared_ptr<PlatformSpawner> m_PlatformSpawner;
	std::shared_ptr<GameObject> m_RightWall;
	std::shared_ptr<GameObject> m_LeftWall;
	std::shared_ptr<GameObject> m_Floor;

	std::shared_ptr<NumberWidget> m_DistanceScoreWidget;
	std::shared_ptr<NumberWidget> m_PlatformScoreWidget;
	std::shared_ptr<NumberWidget> m_LifesWidget;

	bool m_bGameStarted = false;
	int32_t m_DistanceScore = 0;
	int32_t m_PlatformScore = 0;
	int32_t m_PlayerLifes = 0;
	Math::Vector2D m_HorizontalBounds;
	double m_MinAspectRatio = 1.5;

	std::random_device m_RandomDevice;
	std::default_random_engine m_RandomEngine{ m_RandomDevice() };
	double m_EnemySpawnProbability = 0.05;
	double m_AbilitySpawnFrequency = 50;
	std::bernoulli_distribution m_EnemySpawnDistribution{ m_EnemySpawnProbability };
};