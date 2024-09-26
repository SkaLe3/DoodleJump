#include "MenuScene.h"
#include "GameModes/MenuGameMode.h"

MenuScene::MenuScene()
{

}

void MenuScene::Start()
{
	m_GameMode = std::make_shared<MenuGameMode>();
	Scene::Start();
}

void MenuScene::Tick(float deltaTime)
{
	Scene::Tick(deltaTime);
}
