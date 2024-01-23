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
	virtual void Start() override;
	virtual void Tick(double DeltaTime) override;



private:

	Math::Vector2D horizontalBounds;

	std::shared_ptr<CameraComponent> camera;

};