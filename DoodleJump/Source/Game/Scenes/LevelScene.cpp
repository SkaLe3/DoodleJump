#include "LevelScene.h"
#include "GameModes/DJGameMode.h"


void LevelScene::Start()
{
	m_GameMode = std::make_shared<DJGameMode>();
	Scene::Start();
}
