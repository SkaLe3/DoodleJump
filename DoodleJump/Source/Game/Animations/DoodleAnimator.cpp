#include "DoodleAnimator.h"
#include "Core/Base/AssetManager.h"
#include <functional>



DoodleAnimator::DoodleAnimator(Doodle* owner) : m_Owner(owner)
{
	m_AnimMachine = AnimationMachine::Create();
	m_AnimMachine->CreateState("left", -1);
	m_AnimMachine->CreateState("right", -1);
	m_AnimMachine->SetStateAnimation("left", AssetManager::Get().GetAsset<Animation>("A_FrogDoodleLeft"));
	m_AnimMachine->SetStateAnimation("right", AssetManager::Get().GetAsset<Animation>("A_FrogDoodleRight"));
	m_AnimMachine->SetEntryState("left");

	auto left_right = [=]() { return m_Owner->GetLookHDirection() > 0; };
	auto right_left = [=]() { return m_Owner->GetLookHDirection() < 0; };
	AddTransition("left", "right", left_right);
	AddTransition("right", "left", right_left);
}
