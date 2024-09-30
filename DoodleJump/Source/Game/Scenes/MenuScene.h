#pragma once
#include "World/Scene.h"

class MenuScene : public Scene
{
public:
	MenuScene() = default;

	//~ Begin Scene Interface
	virtual void Start() override;
	//~ End Scene Interface
};