#pragma once
#include "Entities/GameMode.h"
#include <memory>


class DJGameMode : public GameMode
{
public:
	DJGameMode();

	virtual void Start() override {}
	virtual void Tick(double DeltaTime) override;

private:
	Sprite* sprite;
	Sprite* quad;
};