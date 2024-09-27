#pragma once
#include "MySprite.h"
#include "Animation.h"

#include <vector>
#include <memory>

class AnimationState
{
public:
	/* Resets frame index*/
	inline void Reset() { m_Index = 0; }

	inline std::shared_ptr<MySprite> GetFrame() { return m_Animation[m_Index]; }
	inline double GetStateDuration() { return m_Animation.size() * m_FrameDuration; }
	inline double GetFrameDuration() { return m_FrameDuration; }

	inline void AddFrame(std::shared_ptr<MySprite> frame) { m_Animation.push_back(frame); }
	inline void NextFrame() { m_Index = ++m_Index % m_Animation.size(); }

	void SetFrameDuration(double frameDuration) { m_FrameDuration = frameDuration; }

private:
	using AnimationStateVec = std::vector<std::shared_ptr<MySprite>>;

	AnimationStateVec m_Animation;
	double m_FrameDuration;
	size_t m_Index = 0;
};
