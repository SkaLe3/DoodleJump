#pragma once
#include "Entities/GameObject.h"

class Platform : public GameObject
{
public:
	Platform();
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;

	void Pass();
	bool IsPassed();
	void Reset();

public:
	std::shared_ptr<SpriteComponent> GetSpriteComponent() const { return spriteComponent; }

protected:
	std::shared_ptr<SpriteComponent> spriteComponent;

	bool bPassed;
};