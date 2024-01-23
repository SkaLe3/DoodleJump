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

	float GetDeltaTime() { return DeltaTime; }
	void Update();

	template<class T>
	std::shared_ptr<Scene> CreateScene()
	{
		std::shared_ptr<Scene> newScene = std::make_shared<T>();
		scenes.push_back(newScene);
		return newScene;
	}
	void SetCurrentScene(std::shared_ptr<Scene> scene);
	std::shared_ptr<Scene> GetCurrentScene();

	void Init(int32_t w, int32_t h);

	static std::shared_ptr<World> Create()
	{
		sInstance = std::make_shared<World>();
		return sInstance;
	}
	static std::shared_ptr<World> Get() { return sInstance; }
private:
	float DeltaTime;

	int32_t width, height;

	std::vector<std::shared_ptr<Scene>> scenes;
	std::shared_ptr<Scene> currentScene;

	static std::shared_ptr<World> sInstance;

	friend class MyFramework;


};
