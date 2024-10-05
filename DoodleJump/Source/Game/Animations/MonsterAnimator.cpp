#include "MonsterAnimator.h"
#include "Core/Base/AssetManager.h"
#include "GameObjects/Monster.h"

MonsterAnimator::MonsterAnimator(Monster* owner) : m_Owner(owner)
{
	m_AnimMachine = AnimationMachine::Create();
	m_AnimMachine->CreateState("idle", -1);
	m_AnimMachine->CreateState("death", 0.065);
	std::shared_ptr<Animation> idleAnim = AssetManager::Get().GetAsset<Animation>("A_UnderwaterMonsterIdle");
	std::shared_ptr<Animation> deathAnim = AssetManager::Get().GetAsset<Animation>("A_UnderwaterMonsterDeath");
	deathAnim->SetLoop(true);
	m_AnimMachine->SetStateAnimation("idle", idleAnim);
	m_AnimMachine->SetStateAnimation("death", deathAnim);
	m_AnimMachine->SetEntryState("idle");

	auto idle_death = [=]() { return m_Owner->IsDying(); };
	AddTransition("idle", "death", idle_death);	
}
