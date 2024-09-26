#pragma once
#include "Entities/GameObject.h"

class Background : public GameObject
{
public:
	Background();	
	~Background();		  

	//~ Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;
	//~ End Object Interface

	std::shared_ptr<SpriteComponent> GetSprite() const { return m_SpriteComponent; }

private:
	std::shared_ptr<SpriteComponent> m_SpriteComponent;
};