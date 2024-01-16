#pragma once
#include "Object.h"
#include <memory>

class GameObject;

class GameMode : public Object
{
public:
	virtual void Start() override {}
	virtual void Tick(double DeltaTime) override {}

protected:
	std::shared_ptr<GameObject> player;
};