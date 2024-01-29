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
	gameMode->Start();

	for (std::shared_ptr<GameObject>& object : tickObjects) { object->Start(); }
	for (std::shared_ptr<GameComponent>& component : tickComponents) { component->Start(); }
	for (std::shared_ptr<BoxComponent>& object : collisionObjects) { object->Start(); }
	for (std::shared_ptr<SpriteComponent>& object : drawObjects) { object->Start(); }

	started = true;
}

void Scene::Tick(float deltaTime)
{
	gameMode->Tick(deltaTime);
	UpdateCollisions();
	UpdateObjects(deltaTime);
	RemoveDestroyed();
	ClearDestroyed();

	// Sort in correct draw order
	std::sort(drawObjects.begin(), drawObjects.end(),
		[](std::shared_ptr<SpriteComponent>& s1, std::shared_ptr<SpriteComponent>& s2) {
			return s1->GetTransform().Translation.z < s2->GetTransform().Translation.z;
		});
	Renderer::BeginScene(camera->GetProjection(), camera->GetTransformMatrix());

	for (std::shared_ptr<SpriteComponent>& object : drawObjects)
	{
		Renderer::DrawSprite(object->GetTransformMatrix(), object->GetSprite());
	}
}

void Scene::UpdateCollisions()
{
	for (std::shared_ptr<BoxComponent>& object : collisionObjects)
	{
		ECollisionChannel channel = object->GetCollisionChannel();
		if (!(channel == ECollisionChannel::Character || channel == ECollisionChannel::WorldDynamic))
			continue;

		for (std::shared_ptr<BoxComponent> other : collisionObjects)
		{
			if (!(other != object
				&& object->IsCollisionEnabled()
				&& other->IsCollisionEnabled()
				&& object->GetCollisionResponce(other->GetCollisionChannel()) == ECollisionResponse::Overlap
				&& other->GetCollisionResponce(object->GetCollisionChannel()) == ECollisionResponse::Overlap
				)) continue;

			Math::Vector2D normal;
			double result = Physics::SweptAABB(object->GetCollider(), other->GetCollider(), normal);
			if (result < 1.0)
			{
				object->OnBeginOverlap(other->GetOwner(), normal, result);
				other->OnBeginOverlap(object->GetOwner(), -normal, result);
			}
		}
	}
}

void Scene::UpdateObjects(double deltaTime)
{
	for (std::shared_ptr<GameComponent>& component : tickComponents)
	{
		component->Tick(deltaTime);
	}
	for (std::shared_ptr<GameObject>& object : tickObjects)
	{
		object->Tick(deltaTime);
	}
	for (std::shared_ptr<SpriteComponent>& object : drawObjects)
	{
		object->Tick(deltaTime);
	}
}

void Scene::RemoveDestroyed()
{
	for (auto toDestory : destroyTickObjects)
	{
		auto it = std::find(tickObjects.begin(), tickObjects.end(), toDestory);
		if (it != tickObjects.end())
		{
			tickObjects.erase(it);
		}
	}
	for (auto toDestory : destroyTickComponents)
	{
		auto it = std::find(tickComponents.begin(), tickComponents.end(), toDestory);
		if (it != tickComponents.end())
		{
			(*it)->RemoveOwner();
			tickComponents.erase(it);
		}
	}
	for (auto toDestory : destroyCollisionObjects)
	{
		auto it = std::find(collisionObjects.begin(), collisionObjects.end(), toDestory);
		if (it != collisionObjects.end())
		{
			(*it)->DetachFromParent();
			(*it)->RemoveOwner();
			collisionObjects.erase(it);
		}
	}
	for (auto toDestory : destroyDrawObjects)
	{
		auto it = std::find(drawObjects.begin(), drawObjects.end(), toDestory);
		if (it != drawObjects.end())
		{
			(*it)->DetachFromParent();
			(*it)->RemoveOwner();
			drawObjects.erase(it);
		}
	}
}

void Scene::ClearDestroyed()
{
	destroyTickObjects.clear();
	destroyTickComponents.clear();
	destroyCollisionObjects.clear();
	destroyDrawObjects.clear();
}

void Scene::SetViewportSize(uint32_t width, uint32_t height)
{
	viewportWidth = width;
	viewportHeight = height;
}

std::shared_ptr<GameObject> Scene::GetObject(GameObject* object)
{
	auto it = std::find_if(tickObjects.begin(), tickObjects.end(), [object](const auto& ptr) {
		return ptr.get() == object;
		});
	// No need to check for found, "object" always exist in tickObjects vector
	return *it;
}


std::shared_ptr<GameComponent> Scene::GetComponent(GameComponent* component)
{
	auto tc = std::find_if(tickComponents.begin(), tickComponents.end(), [component](const auto& ptr) {
		return ptr.get() == component;
		});
	if (tc != tickComponents.end())
		return *tc;

	auto cc = std::find_if(collisionObjects.begin(), collisionObjects.end(), [component](const auto& ptr) {
		return ptr.get() == component;
		});
	if (cc != collisionObjects.end())
		return *cc;

	auto dc = std::find_if(drawObjects.begin(), drawObjects.end(), [component](const auto& ptr) {
		return ptr.get() == component;
		});
	if (dc != drawObjects.end())
		return *dc;

	return nullptr;
}

Math::Vector2D Scene::GetMousePosition()
{
	Math::Vector4D mousePos = { EventHandler::Get()->GetMousePosition(), 0, 1 };

	Math::Mat4 projection = Math::Inverse(camera->GetProjection());
	Math::Mat4 transform = camera->GetTransformMatrix();

	return  transform * projection * mousePos;
}

std::shared_ptr<CameraComponent> Scene::GetRenderCamera()
{
	return camera;
}

std::shared_ptr<GameMode> Scene::GetGameMode()
{
	return gameMode;
}

void Scene::UseCamera(std::shared_ptr<CameraComponent> cc)
{
	camera = cc;
	camera->SetViewportSize(viewportWidth, viewportHeight);
}

void Scene::DestroyGameObject(std::shared_ptr<Object> object)
{
	destroyTickObjects.push_back(object);
}

void Scene::DestroyTickComponent(std::shared_ptr<Object> object)
{
	destroyTickComponents.push_back(object);
}

void Scene::DestroyCollisionObject(std::shared_ptr<Object> object)
{
	destroyCollisionObjects.push_back(object);
}

void Scene::DestroyDrawObject(std::shared_ptr<Object> object)
{
	destroyDrawObjects.push_back(object);
}

void Scene::ClearScene()
{
	camera = nullptr;
	tickComponents.clear();
	collisionObjects.clear();
	drawObjects.clear();
	tickObjects.clear();
}
