#include "DoodleAnimator.h"
#include "Core/Base/AssetManager.h"
#include "GameObjects/Doodle.h"

#include <functional>


DoodleAnimator::DoodleAnimator(Doodle* owner) : m_Owner(owner)
{
	m_AnimMachine = AnimationMachine::Create();
	m_AnimMachine->CreateState("left", -1);
	m_AnimMachine->CreateState("right", -1);
	m_AnimMachine->CreateState("left-jump", -1);
	m_AnimMachine->CreateState("right-jump", -1);
	m_AnimMachine->CreateState("shoot", -1);
	m_AnimMachine->CreateState("shoot-jump", -1);
	m_AnimMachine->SetStateAnimation("left", AssetManager::Get().GetAsset<Animation>("A_FrogDoodleLeft"));
	m_AnimMachine->SetStateAnimation("right", AssetManager::Get().GetAsset<Animation>("A_FrogDoodleRight"));
	m_AnimMachine->SetStateAnimation("left-jump", AssetManager::Get().GetAsset<Animation>("A_FrogDoodleLeftJump"));
	m_AnimMachine->SetStateAnimation("right-jump", AssetManager::Get().GetAsset<Animation>("A_FrogDoodleRightJump"));
	m_AnimMachine->SetStateAnimation("shoot", AssetManager::Get().GetAsset<Animation>("A_FrogDoodleShoot"));
	m_AnimMachine->SetStateAnimation("shoot-jump", AssetManager::Get().GetAsset<Animation>("A_FrogDoodleShootJump"));
	m_AnimMachine->SetEntryState("left");


	auto left_right = [=]() { return  m_Owner->GetLookHDirection() > 0; };
	auto right_left = [=]() { return  m_Owner->GetLookHDirection() < 0; };
	auto left_lj = [=]() { return m_Owner->IsJumping();};
	auto lj_left = [=]() { return !m_Owner->IsJumping();};
	auto right_rj = [=]() { return m_Owner->IsJumping();};
	auto rj_right = [=]() { return !m_Owner->IsJumping();};
	auto lj_rj = [=]() { return m_Owner->GetLookHDirection() > 0;};
	auto rj_lj = [=]() { return m_Owner->GetLookHDirection() < 0;};
	auto shoot_left = [=]() { return !m_Owner->IsShooting() && m_Owner->GetLookHDirection() < 0; };
	auto left_shoot = [=]()	{ return m_Owner->IsShooting(); };
	auto shoot_right = [=]() { return !m_Owner->IsShooting() && m_Owner->GetLookHDirection() > 0; };
	auto right_shoot = [=]() { return m_Owner->IsShooting(); };
	auto shoot_sj = [=]() { return m_Owner->IsJumping(); };
	auto sj_shoot = [=]() { return !m_Owner->IsJumping(); };
	auto lj_sj = [=]() { return m_Owner->IsShooting(); };
	auto sj_lj = [=]() { return !m_Owner->IsShooting() && m_Owner->GetLookHDirection() < 0;; };
	auto rj_sj = [=]() { return m_Owner->IsShooting(); };
	auto sj_rj = [=]() { return !m_Owner->IsShooting() && m_Owner->GetLookHDirection() > 0; };
	AddTransition("left", "right", left_right);
	AddTransition("right", "left", right_left);
	AddTransition("left", "left-jump", left_lj);
	AddTransition("left-jump", "left", lj_left);
	AddTransition("right", "right-jump", right_rj);
	AddTransition("right-jump", "right", rj_right);
	AddTransition("right-jump", "left-jump", rj_lj);
	AddTransition("left-jump", "right-jump", lj_rj);
	AddTransition("shoot", "left", shoot_left);
	AddTransition("left", "shoot", left_shoot);
	AddTransition("shoot", "right", shoot_right);
	AddTransition("right", "shoot", right_shoot);
	AddTransition("shoot", "shoot-jump", shoot_sj);
	AddTransition("shoot-jump", "shoot", sj_shoot);
	AddTransition("left-jump", "shoot-jump", lj_sj);
	AddTransition("shoot-jump", "left-jump", sj_lj);
	AddTransition("right-jump", "shoot-jump", rj_sj);
	AddTransition("shoot-jump", "right-jump", sj_rj);
}
