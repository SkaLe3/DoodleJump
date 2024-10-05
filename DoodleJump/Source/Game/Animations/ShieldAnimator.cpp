#include "ShieldAnimator.h"
#include "Core/Base/AssetManager.h"
#include "GameObjects/Abilities/ImmunityAbility.h"



ShieldAnimator::ShieldAnimator(ImmunityAbility* owner) : m_Owner(owner)
{
	m_AnimMachine = AnimationMachine::Create();
	m_AnimMachine->CreateState("idle", -1);
	m_AnimMachine->CreateState("active", 0.1);
	m_AnimMachine->CreateState("end", 0.2);
	std::shared_ptr<Animation> idleAnim = AssetManager::Get().GetAsset<Animation>("A_ShieldIdle");
	std::shared_ptr<Animation> activeAnim = AssetManager::Get().GetAsset<Animation>("A_ShieldActive");
	std::shared_ptr<Animation> endAnim = AssetManager::Get().GetAsset<Animation>("A_ShieldEnd");
	activeAnim->SetLoop(true);
	endAnim->SetLoop(true);
	m_AnimMachine->SetStateAnimation("idle", idleAnim);
	m_AnimMachine->SetStateAnimation("active", activeAnim);
	m_AnimMachine->SetStateAnimation("end", endAnim);
	m_AnimMachine->SetEntryState("idle");

	auto idle_active = [=]() { return m_Owner->IsActive(); };
	auto active_end = [=]() { return m_Owner->IsEnding(); };
	AddTransition("idle", "active", idle_active);
	AddTransition("active", "end", active_end);
}
