#pragma once
#include "Scene.h"
#include <memory>

class World
{
public:


	float GetDeltaTime() { return DeltaTime; }

	void Update();


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

