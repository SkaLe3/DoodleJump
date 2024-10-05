#pragma once
#include "Core/Renderer/Animator.h"

class Monster;

class MonsterAnimator : public Animator
{
public:
	MonsterAnimator(Monster* owner);

private:
	Monster* m_Owner;
};
