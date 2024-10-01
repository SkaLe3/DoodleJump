#pragma once
#include "Core/Entities/GameObject.h"

class SpriteComponent;

class PlayButton : public GameObject
{
public:
	PlayButton();
	~PlayButton();

	//~ Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;
	//~ End Object Interface

	void Click();

	std::shared_ptr<SpriteComponent> GetSprite() const { return m_SpriteComponent; }

private:
	std::shared_ptr<SpriteComponent> m_SpriteComponent;
};