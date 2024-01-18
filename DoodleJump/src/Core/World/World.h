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

	std::shared_ptr<Scene> CreateScene();
	std::shared_ptr<Scene> GetCurrentScene();

	void Init();

	static std::shared_ptr<World> Create()
	{
		sInstance = std::make_shared<World>();
		return sInstance;
	}
	static std::shared_ptr<World> Get() { return sInstance; }
private:
	float DeltaTime;

	std::vector<std::shared_ptr<Scene>> scenes;
	std::shared_ptr<Scene> currentScene;

	static std::shared_ptr<World> sInstance;

	friend class MyFramework;


};
