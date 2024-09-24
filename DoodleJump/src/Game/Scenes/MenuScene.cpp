#include "MenuScene.h"
#include "GameModes/MenuGameMode.h"

MenuScene::MenuScene()
{

}

void MenuScene::Start()
{
	gameMode = std::make_shared<MenuGameMode>();
	Scene::Start();
}

void MenuScene::Tick(float deltaTime)
{
	Scene::Tick(deltaTime);

}
