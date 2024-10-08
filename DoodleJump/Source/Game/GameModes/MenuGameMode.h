#pragma once
#include "Entities/GameMode.h"

#include <memory>

class CameraObject;
class CameraComponent;
class NumberWidget;
class SpriteWidget;

class MenuGameMode : public GameMode
{
public:
	MenuGameMode();
	~MenuGameMode();

	//~ Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override{};
	//~ End Object Interface

	void Click(Math::Vector2D mousePos);

private:
	Math::Vector2D m_HorizontalBounds;
	std::shared_ptr<CameraObject> m_Camera;
	std::shared_ptr<GameObject> m_PlayButton;

	std::shared_ptr<NumberWidget> m_HighScoreWidget;
	std::shared_ptr<NumberWidget> m_LastScoreWidget;
	std::shared_ptr<NumberWidget> m_HighPlatformWidget;
	std::shared_ptr<NumberWidget> m_LastPlatformWidget;

	double m_HighScore;
	double m_LastScore;
	double m_HighPlat;
	double m_LastPlat;

	double m_MinAspectRatio = 2;
};