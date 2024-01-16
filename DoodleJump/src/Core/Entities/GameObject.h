#pragma once

#include "Object.h"
#include "Math/MyMath.h"

#include "World/World.h"
#include "World/Scene.h"
#include <memory>
//
#include "Components/BoxComponent.h"
//

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
	virtual void Start() override;
	virtual void Tick(double DeltaTime) override;
	Math::Transform& GetTransform();
	std::shared_ptr<BoxComponent> GetBoxComponent() { return boxComponent; }
	Math::Vector2D GetLocation();
protected:
	std::shared_ptr<SceneComponent> rootComponent;
	std::shared_ptr<BoxComponent> boxComponent;
};