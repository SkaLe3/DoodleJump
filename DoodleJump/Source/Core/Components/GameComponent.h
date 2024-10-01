#pragma once
#include "Math/MyMath.h"
#include "Entities/Object.h"

class GameObject;

class GameComponent : public Object
{
public:
	void SetOwner(std::shared_ptr<GameObject> object) { m_Owner = object; }
	void RemoveOwner() { m_Owner = nullptr; }
	std::shared_ptr<GameObject> GetOwner() { return m_Owner; }

protected:
	std::shared_ptr<GameObject> m_Owner;
};

