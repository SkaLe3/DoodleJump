#include "AnimationMachine.h"


std::shared_ptr<AnimationMachine> AnimationMachine::Create()
{
	return std::make_shared<AnimationMachine>();
}

void AnimationMachine::Update(double deltaTime)
{
	double frameDuration = m_ActiveState->GetFrameDuration();
	if (frameDuration == -1) 
	{
		// Always return for one-frame animations (they should have frame duration value equal to -1)
		return;
	}
	if (m_ElapsedTime < frameDuration)
	{
		m_ElapsedTime += deltaTime;
		return;
	}

	m_ElapsedTime -= frameDuration;
	m_ActiveState->NextFrame();
	m_ElapsedTime += deltaTime;
}

void AnimationMachine::SwitchState(const std::string& key)
{
	std::shared_ptr<AnimationState> newState;
	if (m_States.count(key))
	{
		newState = m_States[key];
	}
	m_ActiveState = newState;
	m_ActiveState->Reset();
	m_ElapsedTime = 0;
}

void AnimationMachine::CreateState(const std::string& key, double frameDuration)
{
	m_States[key] = std::make_shared<AnimationState>();
	m_States[key]->SetFrameDuration(frameDuration);
}

void AnimationMachine::AddFrame(const std::string& state, std::shared_ptr<MySprite> frame)
{
	if (m_States.count(state))
	{
		m_States[state]->AddFrame(frame);
	}
}

void AnimationMachine::SetEntryState(const std::string& key)
{
	m_EntryStateKey = key;
	if (m_States.count(key))
	{
		m_ActiveState = m_States[key];
	}
}
