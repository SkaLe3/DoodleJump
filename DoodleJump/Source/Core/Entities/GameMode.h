#pragma once
#include "Object.h"
#include "Core/Math/MyMath.h"


class GameObject;

class GameMode : public Object
{
public:
	std::shared_ptr<GameObject> GetPlayer() { return m_Player; }
	inline const Math::Vector2D GetViewArea() const { return m_ViewArea; }

protected:
	std::shared_ptr<GameObject> m_Player;

	Math::Vector2D m_MaxViewArea = { 36, 108 }; /* Maximum size of a scene in game coordinates */
	Math::Vector2D m_ViewArea; /* Visible part of a scene */
};