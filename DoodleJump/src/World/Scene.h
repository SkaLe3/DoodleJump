#pragma once
#include <vector>
#include <memory>

class GameObject;
class GameMode;
class GameComponent;

class Scene
{
public:

	Scene();
	void Start();
	void Tick(float DeltaTime);

	template<class T>
	std::shared_ptr<T> CreateComponent()
	{ 
		// Somehow add owner to GameComponent
		std::shared_ptr<T> obj = std::make_shared<T>();
		components.push_back(obj);
		return obj;
	}
	template<class T>
	std::shared_ptr<GameObject> SpawnGameObject()
	{
		std::shared_ptr<T> obj = std::make_shared<T>();
		gameObjects.push_back(obj);
		return obj;
	}

private:
	std::shared_ptr<GameMode> gameMode;

	std::vector<std::shared_ptr<GameComponent>> components;
	std::vector<std::shared_ptr<GameObject>> gameObjects;
};