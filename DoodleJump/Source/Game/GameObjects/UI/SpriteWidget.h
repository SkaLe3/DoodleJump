#pragma once
#include "Core/Entities/GameObject.h"

class SpriteWidget : public GameObject
{
public:
	SpriteWidget();
	~SpriteWidget();

	//~ Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;
	//~ End Object Interface

	void SetCoordinates(Math::Vector2D coords);
	std::shared_ptr<SpriteComponent> GetSprite();

private:
	std::shared_ptr<SpriteComponent> m_SpriteComponent;
	Math::Vector2D m_Coordinates;
};