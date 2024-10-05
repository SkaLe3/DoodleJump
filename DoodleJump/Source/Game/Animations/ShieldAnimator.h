#pragma once
#include "Core/Renderer/Animator.h"

class ImmunityAbility;

class ShieldAnimator : public Animator
{
public:
	ShieldAnimator(ImmunityAbility* owner);

private:
	ImmunityAbility* m_Owner;
};