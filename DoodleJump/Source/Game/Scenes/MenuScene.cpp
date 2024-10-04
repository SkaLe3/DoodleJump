#include "MenuScene.h"
#include "GameModes/MenuGameMode.h"


void MenuScene::Start()
{
	m_GameMode = std::make_shared<MenuGameMode>();
	Scene::Start();
}