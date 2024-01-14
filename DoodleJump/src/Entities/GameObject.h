#pragma once

#include "Object.h"
#include "Math/MyMath.h"

#include "World/World.h"
#include "World/Scene.h"
#include <memory>

class SceneComponent;
class BoxComponent;

class GameObject : public Object
{
public:
	GameObject();
	template<class T>
	std::shared_ptr<T> CreateComponent()	
	{
		return GetScene()->CreateComponent<T>();
	}

	Math::Transform& GetTransform() const;
private:
	std::shared_ptr<SceneComponent> rootComponent;
	std::shared_ptr<BoxComponent> boxComponent;
};