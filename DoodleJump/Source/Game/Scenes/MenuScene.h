#pragma once
#include "World/Scene.h"

class MenuScene : public Scene
{
public:
	MenuScene();

	//~ Begin Scene Interface
	virtual void Start() override;
	virtual void Tick(float deltaTime) override;
	//~ End Scene Interface
};