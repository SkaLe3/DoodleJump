#pragma once
#include "World/Scene.h"

class MenuScene : public Scene
{
public:
	MenuScene();

	virtual void Start() override;
	virtual void Tick(float deltaTime) override;

};