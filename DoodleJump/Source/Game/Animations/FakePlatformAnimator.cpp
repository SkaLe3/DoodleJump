#include "FakePlatformAnimator.h"
#include "Core/Base/AssetManager.h"


FakePlatformAnimator::FakePlatformAnimator(FakePlatform* owner)
	: m_Owner(owner)
{
	m_AnimMachine = AnimationMachine::Create();
	m_AnimMachine->CreateState("break", 0.08);
	m_AnimMachine->CreateState("idle", -1);
	m_AnimMachine->SetStateAnimation("break", AssetManager::Get().GetAsset<Animation>("A_CocosPlatformBreak"));
	m_AnimMachine->SetStateAnimation("idle", AssetManager::Get().GetAsset<Animation>("A_CocosPlatformIdle"));
	m_AnimMachine->SetEntryState("idle");

	auto idle_break = [=]() { return m_Owner->IsBroken(); };
	auto break_idle = [=]() { return !m_Owner->IsBroken(); };
	AddTransition("idle", "break", idle_break);
	AddTransition("break", "idle", break_idle);
}
