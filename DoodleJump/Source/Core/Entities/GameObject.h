#pragma once
#include "Object.h"
#include "World/World.h"
#include "World/Scene.h"

#include <string>


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
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;


	Math::Transform& GetTransform();
	std::shared_ptr<BoxComponent> GetBoxComponent();
	Math::Vector2D GetLocation();
	void SetLocation(const Math::Vector& location);

	void SetTag(const std::string& newTag);
	std::string GetTag();
protected:
	std::shared_ptr<SceneComponent> rootComponent;
	std::shared_ptr<BoxComponent> boxComponent;

	std::string tag;
};