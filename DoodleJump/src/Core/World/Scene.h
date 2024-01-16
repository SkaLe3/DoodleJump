#pragma once

#include "Components/BoxComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/CameraComponent.h"
#include "Math/Vector2D.h"

#include <vector>
#include <memory>
class GameObject;
class GameMode;
class GameComponent;
class CameraComponent;

class Scene
{
public:

	Scene();
	void Start();
	void Tick(float DeltaTime);

public:
	template<class T>
	std::shared_ptr<T> CreateComponent()
	{ 
		std::shared_ptr<T> component = std::make_shared<T>();
		tickComponents.push_back(component);
		if (started)
			component->Start();
		return component;
	}
	template<>
	std::shared_ptr<BoxComponent> CreateComponent<BoxComponent>()
	{
		std::shared_ptr<BoxComponent> box = std::make_shared<BoxComponent>();
		collisionObjects.push_back(box);
		if (started)
			box->Start();
		return box;
	}
	template<>
	std::shared_ptr<SpriteComponent> CreateComponent<SpriteComponent>()
	{
		std::shared_ptr<SpriteComponent> sprite = std::make_shared<SpriteComponent>();
		drawObjects.push_back(sprite);
		if (started)
			sprite->Start();
		return sprite;
	}

	template<class T>
	std::shared_ptr<GameObject> SpawnGameObject()
	{
		std::shared_ptr<T> obj = std::make_shared<T>();
		tickObjects.push_back(obj);
		if (started)
			obj->Start();
		return obj;
	}

	void SetViewportSize(uint32_t width, uint32_t height);

	std::shared_ptr<GameObject> GetObject(GameObject* object);
	Math::Vector2D GetMousePosition();
	std::shared_ptr<CameraComponent> GetRenderCamera();

private:
	std::shared_ptr<GameMode> gameMode;

	// Fake ECS
	std::shared_ptr<CameraComponent> camera; // Only one camera per scene supported
	std::vector<std::shared_ptr<GameComponent>> tickComponents;
	std::vector<std::shared_ptr<BoxComponent>> collisionObjects;
	std::vector<std::shared_ptr<SpriteComponent>> drawObjects;
	std::vector<std::shared_ptr<GameObject>> tickObjects;

	bool started = false;

	uint32_t viewportWidth;
	uint32_t viewportHeight;
};