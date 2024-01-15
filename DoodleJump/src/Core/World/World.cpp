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

void World::Init()
{
	currentScene = CreateScene();
	currentScene->SetViewportSize(400, 800);
	currentScene->Start();
}


std::shared_ptr<World> GetWorld() {
	return World::Get();
}

std::shared_ptr<Scene> GetScene() {
	return World::Get()->GetCurrentScene();
}
