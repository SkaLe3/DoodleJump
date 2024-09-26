#pragma once
#include "SceneComponent.h"
#include "Renderer/MySprite.h"
#include "Renderer/AnimationMachine.h"


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
	void SetAnimationMachine(std::shared_ptr<AnimationMachine> animMachine);
	void SwitchAnimationState(const std::string& key); // Temporary
private:
	std::shared_ptr<MySprite> sprite;
	std::shared_ptr<AnimationMachine> m_AnimationMachine;

	bool bAnimationEnabled = false;

};