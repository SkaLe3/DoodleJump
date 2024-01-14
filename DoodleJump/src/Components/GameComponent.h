#pragma once
#include "Math/MyMath.h"
#include "Entities/Object.h"
#include <memory>

class GameObject;

class GameComponent : public Object
{
public:
	virtual ~GameComponent() {}

protected:
	std::shared_ptr<GameObject> owner;
};

