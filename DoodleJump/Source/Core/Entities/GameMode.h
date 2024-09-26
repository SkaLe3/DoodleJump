#pragma once
#include "Object.h"
#include <memory>

class GameObject;

class GameMode : public Object
{
public:
	std::shared_ptr<GameObject> GetPlayer() { return m_Player; }

protected:
	std::shared_ptr<GameObject> m_Player;
};