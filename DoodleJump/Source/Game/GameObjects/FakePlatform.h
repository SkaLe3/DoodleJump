#pragma once
#include "Platform.h"

class FakePlatform : public Platform
{
public:
	FakePlatform();

	//~ Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	//~ End Object Interface

	void OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime);

	void Break();

private:
	bool m_bBroken = false;
	double m_Timer = 0;
};