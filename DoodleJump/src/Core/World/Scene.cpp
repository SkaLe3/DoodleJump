#include "Scene.h"
#include "Entities/GameMode.h"
#include "Game/DJGameMode.h"
#include "Entities/GameObject.h"
#include "Components/GameComponent.h"
#include "Components/SpriteComponent.h"
#include "Framework.h"
#include "Math/MyMath.h"
#include "Components/CameraComponent.h"
#include "Renderer/Renderer.h"
#include <iostream>
#include <sstream>


Scene::Scene()
{
	
}

void Scene::Start()
{
	gameMode = std::make_shared<DJGameMode>();
	camera->SetViewportSize(viewportWidth, viewportHeight);
	for (std::shared_ptr<GameComponent>& component : tickComponents)
	{
		component->Start();
	}
	for (std::shared_ptr<GameObject>& object : tickObjects)
	{
		object->Start();
	}
	for (std::shared_ptr<GameComponent>& object : collisionObjects)
	{
		object->Start();
	}

	for (std::shared_ptr<SpriteComponent>& object : drawObjects)
	{
		object->Start();
	}
	
}

void Scene::Tick(float DeltaTime)
{

	for (std::shared_ptr<GameComponent>& component : tickComponents)
	{
		component->Tick(DeltaTime);
	}
	for (std::shared_ptr<GameObject>& object : tickObjects)
	{
		object->Tick(DeltaTime);
	}
	for (std::shared_ptr<GameComponent>& object : collisionObjects)
	{
		// Handle collisions
	}

	gameMode->Tick(DeltaTime);
	camera->Tick(DeltaTime);

	Renderer::BeginScene(camera->GetProjection(), camera->GetTransformMatrix());

	// TODO: Sort by Z axis
	for (std::shared_ptr<SpriteComponent>& object : drawObjects)
	{
		Renderer::DrawSprite(object->GetTransformMatrix(), object->GetSpriteComponent());
	}
}

void Scene::SetViewportSize(uint32_t width, uint32_t height)
{
	viewportWidth = width;
	viewportHeight = height;
}

std::shared_ptr<GameObject> Scene::GetObject(GameObject* object)
{
	// Find the shared_ptr with the given raw pointer
	auto it = std::find_if(tickObjects.begin(), tickObjects.end(), [object](const auto& ptr) {
		return ptr.get() == object;
		});
	// No need to check for found, "object" always exist in tickObjects vector
	return *it;
}

