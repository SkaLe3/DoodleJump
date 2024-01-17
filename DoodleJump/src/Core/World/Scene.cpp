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
#include "Input/EventHandler.h"
#include "Components/BoxComponent.h"
#include "CollisionSystem.h"

#include <algorithm>

#include <iostream>
#include <sstream>


Scene::Scene() : viewportWidth(100), viewportHeight(100)
{
	
}

void Scene::Start()
{

	
	gameMode = std::make_shared<DJGameMode>();
	gameMode->Start();

	auto it = std::find_if(tickComponents.begin(), tickComponents.end(), [](const auto& ptr) {
		return (dynamic_pointer_cast<CameraComponent>(ptr) != nullptr); });
	if (it != tickComponents.end())
		camera = static_pointer_cast<CameraComponent>(*it);

	camera->SetViewportSize(viewportWidth, viewportHeight);


	for (std::shared_ptr<GameObject>& object : tickObjects)
	{
		object->Start();
	}
	for (std::shared_ptr<GameComponent>& component : tickComponents)
	{
		component->Start();
	}
	for (std::shared_ptr<BoxComponent>& object : collisionObjects)
	{
		object->Start();
	}

	for (std::shared_ptr<SpriteComponent>& object : drawObjects)
	{
		object->Start();
	}

	started = true;
	
	
}

void Scene::Tick(float DeltaTime)
{
	for (std::shared_ptr<BoxComponent>& object : collisionObjects)
	{
		ECollisionChannel channel = object->GetCollisionChannel();
		if (channel == ECollisionChannel::Character || channel == ECollisionChannel::WorldDynamic )
		{
			for (std::shared_ptr<BoxComponent> other : collisionObjects)
			{
				if (other != object
					&& object->IsCollisionEnabled()
					&& other->IsCollisionEnabled()
					&& object->GetCollisionResponce(other->GetCollisionChannel()) == ECollisionResponse::Overlap
					&& other->GetCollisionResponce(object->GetCollisionChannel()) == ECollisionResponse::Overlap
					)
				{
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

	}

	for (std::shared_ptr<GameComponent>& component : tickComponents)
	{
		component->Tick(DeltaTime);
	}
	for (std::shared_ptr<GameObject>& object : tickObjects)
	{
		object->Tick(DeltaTime);
	}

	gameMode->Tick(DeltaTime);


	// Correct Draw order
	std::sort(drawObjects.begin(), drawObjects.end(),
		[](std::shared_ptr<SpriteComponent>& s1, std::shared_ptr<SpriteComponent>& s2) {
			return s1->GetTransform().Translation.z < s2->GetTransform().Translation.z;
		});

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

