#pragma once
#include "Core/Renderer/Animator.h"
#include "GameObjects/FakePlatform.h"

class FakePlatformAnimator : public Animator
{
public:
	FakePlatformAnimator(FakePlatform* owner);

private:
	FakePlatform* m_Owner;
};