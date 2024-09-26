#pragma once
#include "Entities/GameObject.h"

class Platform : public GameObject
{
public:
	Platform();
	~Platform();

	//~ Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;
	//~ End Object Interface

	void Pass();
	bool IsPassed();
	void Reset();

	std::shared_ptr<SpriteComponent> GetSprite() const { return m_SpriteComponent; }

protected:
	std::shared_ptr<SpriteComponent> m_SpriteComponent;
	bool m_bPassed;
};