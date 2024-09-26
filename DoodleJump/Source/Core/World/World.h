#pragma once
#include <memory>
#include <vector>

class Scene;
class World;
class GameMode;

std::shared_ptr<World> GetWorld();
std::shared_ptr<Scene> GetScene();
std::shared_ptr<GameMode> GetGameMode();

class World
{
public:
	static std::shared_ptr<World> Create();
	static std::shared_ptr<World> Get() { return s_Instance; }

public:
	float GetDeltaTime() { return m_DeltaTime; }
	void Update();
	void Init(int32_t w, int32_t h);
	void Shutdown();

	template<class T>
	void OpenScene()
	{
		CreateScene<T>();
		m_ShouldSwitchToLastScene = true;
	}

	template<class T>
	std::shared_ptr<Scene> CreateScene()
	{
		std::shared_ptr<Scene> newScene = std::make_shared<T>();
		m_Scenes.push_back(newScene);
		return newScene;
	}

	void SetCurrentScene(std::shared_ptr<Scene> scene);
	std::shared_ptr<Scene> GetCurrentScene();

private:
	static std::shared_ptr<World> s_Instance;

	std::vector<std::shared_ptr<Scene>> m_Scenes;
	std::shared_ptr<Scene> m_CurrentScene;

	int32_t m_Width, m_Height;
	float m_DeltaTime;
	bool m_ShouldSwitchToLastScene = false;

	friend class MyFramework;
};
