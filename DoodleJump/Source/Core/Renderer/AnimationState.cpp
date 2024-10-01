#include "AnimationState.h"

void AnimationState::Update(double deltaTime)
{
	if (m_FrameDuration == -1)
	{
		// Always return for one-frame animations (they should have frame duration value equal to -1)
		return;
	}
	if (m_ElapsedTime < m_FrameDuration)
	{
		m_ElapsedTime += deltaTime;
		return;
	}

	m_ElapsedTime -= m_FrameDuration;
	m_ElapsedTime += deltaTime;
	m_Animation->Update();
}
