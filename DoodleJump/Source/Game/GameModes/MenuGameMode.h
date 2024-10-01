#pragma once
#include "Entities/GameMode.h"

#include <memory>

class CameraComponent;
class SpriteWidget;

class MenuGameMode : public GameMode
{
public:
	MenuGameMode();
	~MenuGameMode();

	//~ Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override{};
	virtual void Destroy() override{};
	//~ End Object Interface

	void Click(Math::Vector2D mousePos);

private:
	Math::Vector2D m_HorizontalBounds;
	std::shared_ptr<CameraComponent> m_Camera;
	std::shared_ptr<GameObject> m_PlayButton;
};