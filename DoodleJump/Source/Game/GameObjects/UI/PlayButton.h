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

	std::shared_ptr<SpriteComponent> GetSpriteComponent() const { return m_SpriteComponent.lock(); }

private:
	std::weak_ptr<SpriteComponent> m_SpriteComponent;
};