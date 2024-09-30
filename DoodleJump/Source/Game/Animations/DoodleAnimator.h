#pragma once
#include "Core/Renderer/Animator.h"
#include "GameObjects/Doodle.h"

class DoodleAnimator : public Animator
{
public:
	DoodleAnimator(Doodle* owner);

private:
	Doodle* m_Owner;
};