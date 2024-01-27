#include "World.h"
#include "Scene.h"
#include "Scenes/LevelScene.h"
#include "Scenes/MenuScene.h"

std::shared_ptr<World> World::sInstance = nullptr;

void World::Update()
{
	currentScene->Tick(DeltaTime);
}

void World::SetCurrentScene(std::shared_ptr<Scene> scene)
{
	currentScene = scene;
	currentScene->SetViewportSize(width, height);
	currentScene->Start();
}

std::shared_ptr<Scene> World::GetCurrentScene()
{
	return currentScene;
}

std::shared_ptr<World> World::Create()
{
	sInstance = std::make_shared<World>();
	return sInstance;
}

void World::Init(int32_t w, int32_t h)
{
	width = w;
	height = h;
	currentScene = CreateScene<MenuScene>();
	currentScene->SetViewportSize(w, h);
	currentScene->Start();
}


std::shared_ptr<World> GetWorld() {
	return World::Get();
}

std::shared_ptr<Scene> GetScene() {
	return World::Get()->GetCurrentScene();
}

std::shared_ptr<GameMode> GetGameMode()
{
	return World::Get()->GetCurrentScene()->GetGameMode();
}
