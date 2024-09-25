#pragma once
#include "Entities/GameObject.h"

class SpriteWidget : public GameObject
{
public:
	SpriteWidget();
	~SpriteWidget();
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;

	void SetCoordinates(Math::Vector2D coords);

	std::shared_ptr<SpriteComponent> GetSprite();

private:
	std::shared_ptr<SpriteComponent> spriteComponent;

	Math::Vector2D coordinates;
};