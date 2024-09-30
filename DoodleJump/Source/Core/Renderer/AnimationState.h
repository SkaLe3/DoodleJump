#pragma once
#include "MySprite.h"
#include "Animation.h"

#include <vector>
#include <memory>

class AnimationState
{
public:
	void Update(double deltaTime);

	inline std::shared_ptr<MySprite> GetFrame() { return m_Animation->GetFrame(); }
	inline double GetAnimationDuration() { return m_Animation->Length() * m_FrameDuration; }
	inline double GetFrameDuration() { return m_FrameDuration; }

	inline void Play() { m_Animation->Reset(); m_ElapsedTime = 0; }
	inline void SetAnimation(std::shared_ptr<Animation> animation) { m_Animation = animation; }
	inline void SetFrameDuration(double frameDuration) { m_FrameDuration = frameDuration; }
	inline void SetLoopAnimation(bool bLoop) { m_Animation->SetLoop(bLoop); }

private:
	std::shared_ptr<Animation> m_Animation;
	double m_FrameDuration;
	double m_ElapsedTime = 0;
};
