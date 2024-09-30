#pragma once
#include "World/Scene.h"

class LevelScene : public Scene
{
public:
	LevelScene() = default;

	//~ Begin Scene Interface
	virtual void Start() override;
	//~ End Scene Interface
};