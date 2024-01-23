#pragma once

#include "World/Scene.h"



class LevelScene : public Scene
{
public:
	LevelScene();

	virtual void Start() override;
	virtual void Tick(float DeltaTime) override;

};