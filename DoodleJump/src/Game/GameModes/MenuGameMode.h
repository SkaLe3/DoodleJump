#pragma once
#include "Entities/GameMode.h"
#include "Math/Vector2D.h"

#include <memory>

class CameraComponent;
class SpriteWidget;

class MenuGameMode : public GameMode
{
public:
	MenuGameMode();
	~MenuGameMode();
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;

	void Click(Math::Vector2D mousePos);
private:

	Math::Vector2D horizontalBounds;

	std::shared_ptr<CameraComponent> camera;

	std::shared_ptr<GameObject> playButton;

};