#pragma once
#include "Math/MyMath.h"
#include "Entities/Object.h"

class GameObject;

class GameComponent : public Object, public std::enable_shared_from_this<GameComponent>
{
public:
	inline void SetOwner(std::weak_ptr<GameObject> object) { m_Owner = object; }
	inline void RemoveOwner() { m_Owner.reset(); }
	inline std::weak_ptr<GameObject> GetOwner() { return m_Owner; }
	inline std::weak_ptr<GameComponent> GetSelf() { return weak_from_this(); }

protected:
	std::weak_ptr<GameObject> m_Owner;
};

