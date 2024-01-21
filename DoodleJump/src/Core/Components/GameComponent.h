#pragma once
#include "Math/MyMath.h"
#include "Entities/Object.h"
#include <memory>

class GameObject;

class GameComponent : public Object
{
public:
	virtual ~GameComponent() {}
	virtual void Start() override {}
	virtual void Tick(double DeltaTime) override {}
public:

	void SetOwner(std::shared_ptr<GameObject> object) { owner = object; }
	void RemoveOwner() { owner = nullptr; }
	std::shared_ptr<GameObject> GetOwner() { return owner; }

protected:
	std::shared_ptr<GameObject> owner;
};

