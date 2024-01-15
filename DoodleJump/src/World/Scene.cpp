#include "Scene.h"
#include "Entities/GameMode.h"
#include "Game/DJGameMode.h"
#include "Entities/GameObject.h"
#include "Components/GameComponent.h"
#include "Components/SpriteComponent.h"
#include "Framework.h"
#include "Math/MyMath.h"
Scene::Scene()
{
	
}

void Scene::Start()
{
	gameMode = std::make_shared<DJGameMode>();
	// Call Start for all objects;
	gameObjects[0]->Start();

}

void Scene::Tick(float DeltaTime)
{
	gameObjects[0]->Tick(DeltaTime);
	components[1]->Tick(DeltaTime);

	Sprite* sprite = static_pointer_cast<SpriteComponent>(components[1])->GetSprite();

	Math::Vector vec = gameObjects[0]->GetTransform().Translation;

	drawSprite(sprite, vec.x, vec.y);
}

