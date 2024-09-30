#include "Animator.h"


void Animator::Update(double deltaTime)
{
	std::string activeState = m_AnimMachine->GetActiveName();

	/* iterate through all possible transitions from active state */
	for (const auto& [targetState, tCondition] : m_Transitions[activeState])
	{
		if (tCondition)
		{
			m_AnimMachine->SwitchState(targetState);
		}
	}

	m_AnimMachine->Update(deltaTime);
}

std::shared_ptr<MySprite> Animator::GetFrame()
{
	return m_AnimMachine->GetActiveFrame();
}

void Animator::AddTransition(const std::string& source, const std::string& target, std::function<bool()> condition)
{
	if (m_AnimMachine->IsValidState(source) && m_AnimMachine->IsValidState(target))
	{
		m_Transitions[source][target] = condition;
	}
}
