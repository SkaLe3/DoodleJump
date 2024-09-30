#include "Scene.h"
#include "Entities/GameMode.h"
#include "Entities/GameObject.h"
#include "CollisionSystem.h"
#include "Renderer/Renderer.h"
#include "Input/EventHandler.h"
#include "Components/CameraComponent.h"

#include <algorithm>

Scene::Scene()
{

}

void Scene::Start()
{
	m_GameMode->Start();

	for (std::shared_ptr<GameObject>& object : m_TickObjects) { object->Start(); }
	for (std::shared_ptr<GameComponent>& component : m_TickComponents) { component->Start(); }
	for (std::shared_ptr<BoxComponent>& object : m_CollisionObjects) { object->Start(); }
	for (std::shared_ptr<SpriteComponent>& object : m_DrawObjects) { object->Start(); }

	m_bStarted = true;
}

void Scene::Tick(float deltaTime)
{
	m_GameMode->Tick(deltaTime);
	UpdateCollisions();
	UpdateObjects(deltaTime);
	RemoveDestroyed(); // Removes destroyed objects from registry
	ClearDestroyed(); // Clears vectors containing destroyed objects

	// Sort in correct draw order
	std::sort(m_DrawObjects.begin(), m_DrawObjects.end(),
		[](std::shared_ptr<SpriteComponent>& s1, std::shared_ptr<SpriteComponent>& s2) {
			return s1->GetTransform().Translation.z < s2->GetTransform().Translation.z;
		});
	Renderer::BeginScene(m_Camera->GetProjection(), m_Camera->GetTransformMatrix());

	for (std::shared_ptr<SpriteComponent>& object : m_DrawObjects)
	{
		Renderer::DrawSprite(object->GetTransformMatrix(), object->GetSprite());
	}
}

void Scene::UpdateCollisions()
{
	for (std::shared_ptr<BoxComponent>& object : m_CollisionObjects)
	{
		ECollisionChannel channel = object->GetCollisionChannel();
		if (!(channel == ECollisionChannel::Character || channel == ECollisionChannel::WorldDynamic))
			continue;

		for (std::shared_ptr<BoxComponent> other : m_CollisionObjects)
		{
			if (!(other != object
				&& object->IsCollisionEnabled()
				&& other->IsCollisionEnabled()
				&& object->GetCollisionResponce(other->GetCollisionChannel()) == ECollisionResponse::Overlap
				&& other->GetCollisionResponce(object->GetCollisionChannel()) == ECollisionResponse::Overlap
				)) continue;

			Math::Vector2D normal;
			double entryTime = Physics::SweptAABB(object->GetCollider(), other->GetCollider(), normal);
			if (entryTime < 1.0)
			{
				object->OnBeginOverlap(other->GetOwner(), normal, entryTime * GetWorld()->GetDeltaTime());
				other->OnBeginOverlap(object->GetOwner(), -normal, entryTime * GetWorld()->GetDeltaTime());
			}
		}
	}
}

void Scene::UpdateObjects(double deltaTime)
{
	for (std::shared_ptr<GameComponent>& component : m_TickComponents)
	{
		component->Tick(deltaTime);
	}
	for (std::shared_ptr<GameObject>& object : m_TickObjects)
	{
		object->Tick(deltaTime);
	}
	for (std::shared_ptr<SpriteComponent>& object : m_DrawObjects)
	{
		object->Tick(deltaTime);
	}
}

void Scene::DestroyAll()
{
	for (auto& object : m_TickObjects)
	{
		object->Destroy();
	}
}

void Scene::RemoveDestroyed()
{
	for (auto toDestory : m_DestroyTickObjects)
	{
		auto it = std::find(m_TickObjects.begin(), m_TickObjects.end(), toDestory);
		if (it != m_TickObjects.end())
		{
			m_TickObjects.erase(it);
		}
	}
	for (auto toDestory : m_DestroyTickComponents)
	{
		auto it = std::find(m_TickComponents.begin(), m_TickComponents.end(), toDestory);
		if (it != m_TickComponents.end())
		{
			(*it)->RemoveOwner();
			m_TickComponents.erase(it);
		}
	}
	for (auto toDestory : m_DestroyCollisionObjects)
	{
		auto it = std::find(m_CollisionObjects.begin(), m_CollisionObjects.end(), toDestory);
		if (it != m_CollisionObjects.end())
		{
			(*it)->DetachFromParent();
			(*it)->RemoveOwner();
			m_CollisionObjects.erase(it);
		}
	}
	for (auto toDestory : m_DestroyDrawObjects)
	{
		auto it = std::find(m_DrawObjects.begin(), m_DrawObjects.end(), toDestory);
		if (it != m_DrawObjects.end())
		{
			(*it)->DetachFromParent();
			(*it)->RemoveOwner();
			m_DrawObjects.erase(it);
		}
	}
}

void Scene::ClearDestroyed()
{
	m_DestroyTickObjects.clear();
	m_DestroyTickComponents.clear();
	m_DestroyCollisionObjects.clear();
	m_DestroyDrawObjects.clear();
}

void Scene::SetViewportSize(uint32_t width, uint32_t height)
{
	m_ViewportWidth = width;
	m_ViewportHeight = height;
}

void Scene::GetViewportSize(uint32_t& width, uint32_t& height)
{
   width = m_ViewportWidth;
   height = m_ViewportHeight;
}

std::shared_ptr<GameObject> Scene::GetObject(GameObject* object)
{
	auto it = std::find_if(m_TickObjects.begin(), m_TickObjects.end(), [object](const auto& ptr) {
		return ptr.get() == object;
		});
	// No need to check for found, "object" always exist in tickObjects vector
	return *it;
}


std::shared_ptr<GameComponent> Scene::GetComponent(GameComponent* component)
{
	auto tc = std::find_if(m_TickComponents.begin(), m_TickComponents.end(), [component](const auto& ptr) {
		return ptr.get() == component;
		});
	if (tc != m_TickComponents.end())
		return *tc;

	auto cc = std::find_if(m_CollisionObjects.begin(), m_CollisionObjects.end(), [component](const auto& ptr) {
		return ptr.get() == component;
		});
	if (cc != m_CollisionObjects.end())
		return *cc;

	auto dc = std::find_if(m_DrawObjects.begin(), m_DrawObjects.end(), [component](const auto& ptr) {
		return ptr.get() == component;
		});
	if (dc != m_DrawObjects.end())
		return *dc;

	return nullptr;
}

Math::Vector2D Scene::GetMousePosition()
{
	Math::Vector4D mousePos = { EventHandler::Get()->GetMousePosition(), 0, 1 };

	Math::Mat4 projection = Math::Inverse(m_Camera->GetProjection());
	Math::Mat4 transform = m_Camera->GetTransformMatrix();

	return  transform * projection * mousePos;
}

std::shared_ptr<CameraComponent> Scene::GetRenderCamera()
{
	return m_Camera;
}

std::shared_ptr<GameMode> Scene::GetGameMode()
{
	return m_GameMode;
}

void Scene::UseCamera(std::shared_ptr<CameraComponent> cc)
{
	m_Camera = cc;
	m_Camera->SetViewportSize(m_ViewportWidth, m_ViewportHeight);
}

void Scene::DestroyGameObject(std::shared_ptr<Object> object)
{
	m_DestroyTickObjects.push_back(object);
}

void Scene::DestroyTickComponent(std::shared_ptr<Object> object)
{
	m_DestroyTickComponents.push_back(object);
}

void Scene::DestroyCollisionObject(std::shared_ptr<Object> object)
{
	m_DestroyCollisionObjects.push_back(object);
}

void Scene::DestroyDrawObject(std::shared_ptr<Object> object)
{
	m_DestroyDrawObjects.push_back(object);
}

void Scene::ClearScene()
{
	m_Camera = nullptr;
	m_GameMode = nullptr;
	DestroyAll();
	RemoveDestroyed();
	ClearDestroyed();
}
