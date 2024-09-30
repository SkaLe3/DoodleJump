#pragma once
#include "Core/Renderer/MySprite.h"
#include <vector>
#include <memory>

class Animation
{
public:
	Animation(const std::vector<std::shared_ptr<MySprite>>& animationSource) : m_Frames(animationSource) {}

	void Update();
	inline void Reset() { m_Index = 0; }
	inline void SetLoop(bool bLoop) { m_bLoopAnimation = bLoop; }
	inline std::shared_ptr<MySprite> GetFrame() { return m_Frames[m_Index]; }
	inline size_t Length() { return m_Frames.size(); }

private:
	std::vector<std::shared_ptr<MySprite>> m_Frames;
	size_t m_Index = 0;
	bool m_bLoopAnimation;
};