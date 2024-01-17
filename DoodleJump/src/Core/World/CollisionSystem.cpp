#include "CollisionSystem.h"
#include "Math/Vector.h"
#include "Math/Vector2D.h"

#include <limits>


#include <iostream>
namespace Physics
{

	bool IsColliding(std::shared_ptr<BoxComponent>& object, std::shared_ptr<BoxComponent> other)
	{
		Math::Vector b1 = object->GetTransform().Translation;
		Math::Vector b2 = other->GetTransform().Translation;

		Math::Vector2D b1Size = object->GetHalfSize();
		Math::Vector2D b2Size = object->GetHalfSize();


		double left = (b2.x - b2Size.x) - (b1.x + b1Size.x);
		double right = (b2.x + b2Size.x) - (b1.x - b1Size.x);
		double top = (b2.y + b2Size.y) - (b1.y - b1Size.y);
		double bottom = (b2.y - b2Size.y) - (b1.y + b1Size.y);

		return !(left > 0 || right < 0 || top < 0 || bottom > 0);
	}

	double SweptAABB(std::shared_ptr<BoxComponent>& object, std::shared_ptr<BoxComponent> other, Math::Vector2D& normal)
	{
		// add broad phase to check if there will be a collision, in the next frame
		double dxEntry, dyEntry;
		double dxExit, dyExit;

		Math::Vector b1 = object->GetTransform().Translation;
		Math::Vector b2 = other->GetTransform().Translation;

		Math::Vector2D b1Size = object->GetHalfSize();
		Math::Vector2D b2Size = other->GetHalfSize();

		if (object->GetVelocity().x > 0.0)
		{
			dxEntry = (b2.x - b2Size.x) - (b1.x + b1Size.x);
			dxExit = (b2.x + b2Size.x) - (b1.x - b1Size.x);
		}
		else
		{
			dxEntry = (b2.x + b2Size.x) - (b1.x - b1Size.x);
			dxExit = (b2.x - b2Size.x) - (b1.x + b1Size.x);
		}
		if (object->GetVelocity().y > 0.0)
		{
			dyEntry = (b2.y - b2Size.y) - (b1.y + b1Size.y);
			dyExit = (b2.y + b2Size.y) - (b1.y - b1Size.y);
		}
		else
		{
			dyEntry = (b2.y + b2Size.y) - (b1.y - b1Size.y);
			dyExit = (b2.y - b2Size.y) - (b1.y + b1Size.y);
		}

		double txEntry, tyEntry;
		double txExit, tyExit;

		if (object->GetVelocity().x == 0.0)
		{
			txEntry = - std::numeric_limits<double>::infinity();
			txExit = std::numeric_limits<double>::infinity();
		}
		else
		{
			txEntry = dxEntry / object->GetVelocity().x;
			txExit = dxExit / object->GetVelocity().x;
		}
		if (object->GetVelocity().y == 0.0)
		{
			tyEntry = -std::numeric_limits<double>::infinity();
			tyExit = std::numeric_limits<double>::infinity();
		}
		else
		{
			tyEntry = dyEntry / object->GetVelocity().y;
			tyExit = dyExit / object->GetVelocity().y;

			
		}

		double entryTime = std::max(txEntry, tyEntry);
		double exitTime = std::min(txExit, tyExit);

		if (entryTime > exitTime || txEntry < 0.0 && tyEntry < 0.0 || txEntry > 1.0 || tyEntry > 1.0)
		{
			normal.x = 0.0;
			normal.y = 0.0;
			return 1.0;
		}
		else 
		{
			if (txEntry > tyEntry)
			{
				if (dxEntry < 0.0)
				{
					normal.x = 1.0;
					normal.y = 0.0;
				}
				else
				{
					normal.x = 1.0;
					normal.y = 0.0;
				}
			}
			else
			{
				if (dyEntry < 0.0)
				{
					normal.x = 0.0;
					normal.y = 1.0;
				}
				else
				{
					normal.x = 0.0;
					normal.y = -1.0;
				}
			}

		}

		return entryTime;
	}

}