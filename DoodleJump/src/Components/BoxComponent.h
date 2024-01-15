#pragma once
#include "SceneComponent.h"

class BoxComponent : public SceneComponent
{
public:
	BoxComponent() : SceneComponent() {}

	virtual void Start() override {}
	virtual void Tick(double DeltaTime) override {}
	
private:
	
};