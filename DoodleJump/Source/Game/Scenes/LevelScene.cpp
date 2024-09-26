#include "LevelScene.h"
#include "GameModes/DJGameMode.h"


LevelScene::LevelScene()
{
	
}

void LevelScene::Start()
{
	m_GameMode = std::make_shared<DJGameMode>();
	Scene::Start();
}

void LevelScene::Tick(float deltaTime)
{
	Scene::Tick(deltaTime);
}

