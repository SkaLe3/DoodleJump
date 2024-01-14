#pragma once
#include <vector>
#include <memory>

class GameObject;

class Scene
{
public:
	void Tick(float DeltaTime);

	template<class T>
	std::shared_ptr<T> CreateComponent()
	{
		return std::make_shared<T>();
	}

private:

	std::vector<std::shared_ptr<GameObject>> gameObjects;
};