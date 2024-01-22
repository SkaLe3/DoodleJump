#include "World.h"
#include "Scene.h"

std::shared_ptr<World> World::sInstance = nullptr;

void World::Update()
{
	currentScene->Tick(DeltaTime);
}

std::shared_ptr<Scene> World::CreateScene()
{
	std::shared_ptr<Scene> newScene = std::make_shared<Scene>();
	scenes.push_back(newScene);
	return newScene;
}

std::shared_ptr<Scene> World::GetCurrentScene()
{
	return currentScene;
}

void World::Init(int32_t w, int32_t h)
{
	currentScene = CreateScene();
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
