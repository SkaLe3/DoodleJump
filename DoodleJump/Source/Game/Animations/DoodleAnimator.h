#pragma once
#include "Core/Renderer/Animator.h"

class Doodle;

class DoodleAnimator : public Animator
{
public:
	DoodleAnimator(Doodle* owner);

private:
	Doodle* m_Owner;
};