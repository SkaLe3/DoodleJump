#include "CollisionSystem.h"
#include "Math/Vector.h"
#include "Math/Vector2D.h"
#include "World/World.h"

#include <limits>

namespace Physics
{

	bool IsColliding(const BoxCollider& object, const BoxCollider& other)
	{

		double left = (other.pos.x - other.size.x) - (object.pos.x + object.size.x);
		double right = (other.pos.x + other.size.x) - (object.pos.x - object.size.x);
		double top = (other.pos.y + other.size.y) - (object.pos.y - object.size.y);
		double bottom = (other.pos.y - other.size.y) - (object.pos.y + object.size.y);

		return !(left > 0 || right < 0 || top < 0 || bottom > 0);
	}

	BoxCollider GetBroadPhaseCollider(const BoxCollider& object)
	{
		Math::Vector2D position = object.pos + object.vel * 0.5;
		Math::Vector2D size = object.size  + Math::Abs(object.vel) * 0.5;

		return BoxCollider(position, size, object.vel);
	}



	double SweptAABB(const BoxCollider& object, const BoxCollider& other, Math::Vector2D& normal)
	{
		// Broad-Phase 
		BoxCollider collider = GetBroadPhaseCollider(object);
		if (!IsColliding(collider, other))
			return 1;

		Math::Vector2D dEntry;
		Math::Vector2D dExit;


		if (object.vel.x > 0.0)
		{
			dEntry.x = (other.pos.x - other.size.x) - (object.pos.x + object.size.x);
			dExit.x = (other.pos.x + other.size.x) - (object.pos.x - object.size.x);
		}
		else
		{
			dEntry.x = (other.pos.x + other.size.x) - (object.pos.x - object.size.x);
			dExit.x = (other.pos.x - other.size.x) - (object.pos.x + object.size.x);
		}
		if (object.vel.y > 0.0)
		{
			dEntry.y = (other.pos.y - other.size.y) - (object.pos.y + object.size.y);
			dExit.y = (other.pos.y + other.size.y) - (object.pos.y - object.size.y);
		}
		else
		{
			dEntry.y = (other.pos.y + other.size.y) - (object.pos.y - object.size.y);
			dExit.y = (other.pos.y - other.size.y) - (object.pos.y + object.size.y);
		}

		Math::Vector2D tEntry;
		Math::Vector2D tExit;

		if (object.vel.x == 0.0)
		{
			tEntry.x = - std::numeric_limits<double>::infinity();
			tExit.x = std::numeric_limits<double>::infinity();
		}
		else
		{
			tEntry.x = dEntry.x / object.vel.x;
			tExit.x = dExit.x / object.vel.x;
		}
		if (object.vel.y == 0.0)
		{
			tEntry.y = -std::numeric_limits<double>::infinity();
			tExit.y = std::numeric_limits<double>::infinity();
		}
		else
		{
			tEntry.y = dEntry.y / object.vel.y;
			tExit.y = dExit.y / object.vel.y;
		}

		double entryTime = std::max(tEntry.x, tEntry.y);
		double exitTime = std::min(tExit.x, tExit.y);

		if (entryTime > exitTime || tEntry.x < 0.0 && tEntry.y < 0.0 || tEntry.x > 1.0 || tEntry.y > 1.0)
		{
			normal = { 0, 0 };
			return 1.0;
		}
		else 
		{
			if (tEntry.x > tEntry.y)
			{
				if (dEntry.x < 0.0)
					normal = { 1, 0 };
				else
					normal = { -1, 0 };
			}
			else
			{
				if (dEntry.y < 0.0)
					normal = { 0, 1 };
				else
					normal = { 0, -1 };
			}
		}
		return entryTime;
	}

}