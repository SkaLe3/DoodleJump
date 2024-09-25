#pragma once
#include "Platform.h"

class FakePlatform : public Platform
{
public:
	FakePlatform();

	virtual void Start() override;
	virtual void Tick(double deltaTime) override;

	void OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime);

public:
	void Break();
private:

	bool bBroken = false;
	double timer = 0;

};