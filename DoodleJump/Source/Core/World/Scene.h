#pragma once
#include "Math/MyMath.h"
#include "Components/BoxComponent.h"
#include "Components/SpriteComponent.h"

#include <memory>
#include <vector>

class GameMode;
class GameComponent;
class CameraComponent;
class GameObject;
class Object;


class Scene
{
public:
	Scene();

	virtual void Start();
	virtual void Tick(float deltaTime);

public:
	template<class T>
	std::shared_ptr<T> CreateComponent()
	{
		std::shared_ptr<T> component = std::make_shared<T>();
		m_TickComponents.push_back(component);
		if (m_bStarted)
			component->Start();
		return component;
	}
	template<>
	std::shared_ptr<BoxComponent> CreateComponent<BoxComponent>()
	{
		std::shared_ptr<BoxComponent> box = std::make_shared<BoxComponent>();
		m_CollisionObjects.push_back(box);
		if (m_bStarted)
			box->Start();
		return box;
	}
	template<>
	std::shared_ptr<SpriteComponent> CreateComponent<SpriteComponent>()
	{
		std::shared_ptr<SpriteComponent> sprite = std::make_shared<SpriteComponent>();
		m_DrawObjects.push_back(sprite);
		if (m_bStarted)
			sprite->Start();
		return sprite;
	}
	template<class T>
	std::shared_ptr<T> SpawnGameObject()
	{
		std::shared_ptr<T> obj = std::make_shared<T>();
		m_TickObjects.push_back(obj);
		if (m_bStarted)
			obj->Start();
		return obj;
	}

public:
	void UpdateCollisions();
	void UpdateObjects(double deltaTime);
	void DestroyAll();
	void RemoveDestroyed();
	void ClearDestroyed();

	void SetViewportSize(uint32_t width, uint32_t height);

	std::shared_ptr<GameObject> GetObject(GameObject* object);
	std::shared_ptr<GameComponent> GetComponent(GameComponent* component);
	Math::Vector2D GetMousePosition();
	std::shared_ptr<CameraComponent> GetRenderCamera();
	std::shared_ptr<GameMode> GetGameMode();
	void UseCamera(std::shared_ptr<CameraComponent> cc);

	void DestroyGameObject(std::shared_ptr<Object> object);
	void DestroyTickComponent(std::shared_ptr<Object> object);
	void DestroyCollisionObject(std::shared_ptr<Object> object);
	void DestroyDrawObject(std::shared_ptr<Object> object);

	void ClearScene();

protected:
	std::shared_ptr<GameMode> m_GameMode;

	/* ECS */
	std::shared_ptr<CameraComponent> m_Camera; // Only one camera per scene supported
	std::vector<std::shared_ptr<GameComponent>> m_TickComponents;
	std::vector<std::shared_ptr<BoxComponent>> m_CollisionObjects;
	std::vector<std::shared_ptr<SpriteComponent>> m_DrawObjects;
	std::vector<std::shared_ptr<GameObject>> m_TickObjects;

	std::vector<std::shared_ptr<Object>> m_DestroyTickComponents;
	std::vector<std::shared_ptr<Object>> m_DestroyCollisionObjects;
	std::vector<std::shared_ptr<Object>> m_DestroyDrawObjects;
	std::vector<std::shared_ptr<Object>> m_DestroyTickObjects;

	uint32_t m_ViewportWidth;
	uint32_t m_ViewportHeight;

	bool m_bStarted = false;
};