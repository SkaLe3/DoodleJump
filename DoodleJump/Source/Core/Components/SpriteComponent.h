#pragma once
#include "SceneComponent.h"

class MySprite;
class Animator;

class SpriteComponent : public SceneComponent
{
public:
	SpriteComponent() = default;
	~SpriteComponent();

	//~ Begin Object Interface
	virtual void Start() override {}
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;
	//~ End Object Interface

	void SetSprite(std::shared_ptr<MySprite> newSprite);
	std::shared_ptr<MySprite> GetSprite() const;

	void EnableAnimation();
	void SetAnimator(std::shared_ptr<Animator> animator);
private:
	std::shared_ptr<MySprite> m_Sprite;
	std::shared_ptr<Animator> m_Animator;

	bool m_bAnimationEnabled = false;
};