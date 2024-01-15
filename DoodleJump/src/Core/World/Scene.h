#pragma once
#include <vector>
#include <memory>

#include "Components/BoxComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/CameraComponent.h"

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
		return component;
	}
	template<>
	std::shared_ptr<BoxComponent> CreateComponent<BoxComponent>()
	{
		std::shared_ptr<BoxComponent> box = std::make_shared<BoxComponent>();
		collisionObjects.push_back(static_pointer_cast<GameComponent>(box));
		return box;
	}
	template<>
	std::shared_ptr<SpriteComponent> CreateComponent<SpriteComponent>()
	{
		std::shared_ptr<SpriteComponent> sprite = std::make_shared<SpriteComponent>();
		drawObjects.push_back(sprite);
		return sprite;
	}
	template<>
	std::shared_ptr<CameraComponent> CreateComponent<CameraComponent>()
	{
		camera = std::make_shared<CameraComponent>();
		return camera;
	}
	template<class T>
	std::shared_ptr<GameObject> SpawnGameObject()
	{
		std::shared_ptr<T> obj = std::make_shared<T>();
		tickObjects.push_back(obj);
		return obj;
	}

	void SetViewportSize(uint32_t width, uint32_t height);

	std::shared_ptr<GameObject> GetObject(GameObject* object);

private:
	std::shared_ptr<GameMode> gameMode;

	// Fake ECS
	std::shared_ptr<CameraComponent> camera; // Only one camera per scene supported
	std::vector<std::shared_ptr<GameComponent>> tickComponents;
	std::vector<std::shared_ptr<GameComponent>> collisionObjects;
	std::vector<std::shared_ptr<SpriteComponent>> drawObjects;
	std::vector<std::shared_ptr<GameObject>> tickObjects;

	uint32_t viewportWidth;
	uint32_t viewportHeight;
};