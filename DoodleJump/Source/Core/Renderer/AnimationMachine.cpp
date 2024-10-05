#include "AnimationMachine.h"

std::shared_ptr<AnimationMachine> AnimationMachine::Create()
{
	return std::make_shared<AnimationMachine>();
}

void AnimationMachine::Update(double deltaTime)
{
	GetActive()->Update(deltaTime);
}

void AnimationMachine::SwitchState(const std::string& key)
{
	if (m_States.count(key))
	{
		m_ActiveStateName = key;
	}
	GetActive()->Play();
}

void AnimationMachine::CreateState(const std::string& key, double frameDuration)
{
	m_States[key] = std::make_shared<AnimationState>();
	m_States[key]->SetFrameDuration(frameDuration);
}

void AnimationMachine::SetStateAnimation(const std::string& state, std::shared_ptr<Animation> animation)
{
	if (m_States.count(state))
	{
		m_States[state]->SetAnimation(animation);
	}
}

/* User should always set entry state manually in Animator class*/
void AnimationMachine::SetEntryState(const std::string& state)
{
	if (m_States.count(state))
	{
		m_EntryStateName = state;
		m_ActiveStateName = m_EntryStateName;
	}
}

void AnimationMachine::SetActive(const std::string& state)
{
	if (m_States.count(state))
	{
		m_ActiveStateName = state;
	}
}
