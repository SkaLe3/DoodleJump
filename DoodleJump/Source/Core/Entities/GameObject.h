#pragma once
#include "Object.h"
#include "World/World.h"


class SceneComponent;
class BoxComponent;

class GameObject : public Object, public std::enable_shared_from_this<GameObject>
{
public:
	GameObject();

	//~ Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;
	//~ End Object Interface

	template<class T>
	std::weak_ptr<T> CreateComponent()
	{
		return GetScene()->CreateComponent<T>();
	}
	inline std::weak_ptr<GameObject> GetSelf() { return weak_from_this(); }

	Math::Transform& GetTransform();
	std::shared_ptr<BoxComponent> GetBoxComponent();
	inline std::shared_ptr<SceneComponent> GetRoot() { return m_RootComponent.lock();}
	Math::Vector2D GetLocation();
	std::string GetTag();

	inline void SetRoot(std::weak_ptr<SceneComponent> root) { m_RootComponent = root; }
	void SetLocation(const Math::Vector& location);
	void SetTag(const std::string& newTag);

protected:
	std::weak_ptr<SceneComponent> m_RootComponent;
	std::weak_ptr<BoxComponent> m_BoxComponent;

	std::string m_Tag;
};