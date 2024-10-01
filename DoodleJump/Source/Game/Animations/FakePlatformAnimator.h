#pragma once
#include "Core/Renderer/Animator.h"

class FakePlatform;

class FakePlatformAnimator : public Animator
{
public:
	FakePlatformAnimator(FakePlatform* owner);

private:
	FakePlatform* m_Owner;
};