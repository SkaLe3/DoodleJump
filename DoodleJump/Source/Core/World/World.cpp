#include "World.h"
#include "Scenes/LevelScene.h"
#include "Scenes/MenuScene.h"
#include "Input/EventHandler.h"

std::shared_ptr<World> World::s_Instance = nullptr;

void World::Update()
{
	m_CurrentScene->Tick(m_DeltaTime);
	if (m_ShouldSwitchToLastScene)
	{
		m_CurrentScene->ClearScene();
		EventHandler::Get()->ClearBindings();
		SetCurrentScene(m_Scenes.back());
		m_Scenes.erase(m_Scenes.begin());
		m_ShouldSwitchToLastScene = false;
	}
}

void World::SetCurrentScene(std::shared_ptr<Scene> scene)
{
	m_CurrentScene = scene;
	m_CurrentScene->SetViewportSize(m_Width, m_Height);
	m_CurrentScene->Start();
}

std::shared_ptr<Scene> World::GetCurrentScene()
{
	return m_CurrentScene;
}

std::shared_ptr<World> World::Create()
{
	s_Instance = std::make_shared<World>();
	return s_Instance;
}

void World::Init(int32_t w, int32_t h)
{
	m_Width = w;
	m_Height = h;
	m_CurrentScene = CreateScene<MenuScene>();
	m_CurrentScene->SetViewportSize(w, h);
	m_CurrentScene->Start();
}


void World::Shutdown()
{
	for (auto& scene : m_Scenes)
	{
		scene->ClearScene();
	}
	EventHandler::Get()->ClearBindings();
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
