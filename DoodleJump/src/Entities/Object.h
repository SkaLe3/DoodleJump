#pragma once
#include "GameObject.h"

class Object
{
	virtual void Tick() = 0;

public:
	virtual ~Object() {}
};