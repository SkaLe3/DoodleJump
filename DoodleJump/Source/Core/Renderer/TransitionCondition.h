#pragma once
#include <functional>


class TransitionCondition
{
public:
	TransitionCondition() = default;
	TransitionCondition(std::function<bool()> func) : m_ConditionCheck(func) {}

	void SetCondition(std::function<bool()> func) { m_ConditionCheck = func; }
	operator bool() const { return m_ConditionCheck(); }
private:
	std::function<bool()> m_ConditionCheck;
};