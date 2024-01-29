#include "LevelScene.h"
#include "GameModes/DJGameMode.h"


LevelScene::LevelScene()
{
	
}

void LevelScene::Start()
{
	gameMode = std::make_shared<DJGameMode>();
	Scene::Start();
}

void LevelScene::Tick(float deltaTime)
{
	Scene::Tick(deltaTime);
}

