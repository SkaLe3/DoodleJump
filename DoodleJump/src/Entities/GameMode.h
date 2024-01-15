#pragma once
#include "Object.h"
#include <memory>

class GameObject;

class GameMode : public Object
{

protected:
	std::shared_ptr<GameObject> player;
};