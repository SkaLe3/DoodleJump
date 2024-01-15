#pragma once
#include "Entities/GameObject.h"
#include "Input/InputValue.h"

class SpriteComponent;

class Doodle : public GameObject
{
public:
	Doodle();
	virtual void Start() override;
	virtual void Tick(double DeltaTime) override;

	std::shared_ptr<SpriteComponent> GetSprite() const { return spriteComponent; }

public:
	void Move(InputValue& value);

private:
	std::shared_ptr<SpriteComponent> spriteComponent;
};