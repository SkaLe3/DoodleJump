#pragma once
#include "Object.h"
#include "World/World.h"


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

	//~ Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;
	//~ End Object Interface

	Math::Transform& GetTransform();
	std::shared_ptr<BoxComponent> GetBoxComponent();
	Math::Vector2D GetLocation();
	std::string GetTag();

	void SetLocation(const Math::Vector& location);
	void SetTag(const std::string& newTag);

protected:
	std::shared_ptr<SceneComponent> m_RootComponent;
	std::shared_ptr<BoxComponent> m_BoxComponent;

	std::string m_Tag;
};