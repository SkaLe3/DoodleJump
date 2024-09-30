#include "Animation.h"



void Animation::Update()
{
	if (m_bLoopAnimation)
	{
		m_Index = ++m_Index % m_Frames.size();
		return;
	}
	if (m_Index < m_Frames.size() - 1)
	{
		m_Index++;
	}
}
