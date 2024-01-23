#include "MenuGameMode.h"
#include "World/World.h"
#include "World/Scene.h"
#include "World/CollisionSystem.h"

#include "GameObjects/Doodle.h"
#include "Background.h"
#include "Components/CameraComponent.h"

#include "Renderer/MySprite.h"
#include "GameObjects/UI/MenuController.h"
#include "GameObjects/UI/PlayButton.h"

#include "Scenes/LevelScene.h"


#include "Framework.h"

MenuGameMode::MenuGameMode()
{

}

void MenuGameMode::Start()
{
	GameMode::Start();
	showCursor(true);

	// Spawn Player
	player = GetScene()->SpawnGameObject<MenuController>();
	// Spawn Background
	std::shared_ptr<Background> background = GetScene()->SpawnGameObject<Background>();
	std::shared_ptr<MySprite> spriteRef = std::make_shared<MySprite>("assets/Menu.png");
	background->GetSpriteComponent()->SetSprite(spriteRef);
	background->GetSpriteComponent()->GetTransform().Scale = { 36, 54, 1 };
	background->GetSpriteComponent()->GetTransform().Translation = { 0, 0, -1 };

	// Camera
	camera = GetScene()->GetRenderCamera();
	Math::Vector2D camBounds = camera->GetCameraBounds();
	horizontalBounds = { camera->GetTransform().Translation.x - camBounds.x * 0.5, camera->GetTransform().Translation.x + camBounds.x * 0.5 };


	playButton = GetScene()->SpawnGameObject<PlayButton>();

}

void MenuGameMode::Tick(double DeltaTime)
{
	GameMode::Tick(DeltaTime);
}

void MenuGameMode::Click(Math::Vector2D mousePos)
{
	bool isClicked = Physics::IsColliding({ mousePos, {0.1, 0.1}, {0, 0} }, playButton->GetBoxComponent()->GetCollider());

	GetScene()->ClearScene();

	auto newScene = GetWorld()->CreateScene<LevelScene>();
	GetWorld()->SetCurrentScene(newScene);
	

}
