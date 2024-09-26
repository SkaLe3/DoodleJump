#pragma once
#include "World/Scene.h"

class LevelScene : public Scene
{
public:
	LevelScene();

	//~ Begin Scene Interface
	virtual void Start() override;
	virtual void Tick(float deltaTime) override;
	//~ End Scene Interface
};