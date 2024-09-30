#pragma once
#include "AnimationMachine.h"
#include "TransitionCondition.h"

#include <memory>
#include <unordered_map>
#include <functional>

template <typename T>
using StateMap = std::unordered_map<std::string, T>;

class Animator
{
public:
	virtual ~Animator() {}

	void Update(double deltaTime);
	std::shared_ptr<MySprite> GetFrame();

protected:
	void AddTransition(const std::string& source, const std::string& target, std::function<bool()> condition);
protected:
	std::shared_ptr<AnimationMachine> m_AnimMachine;
	StateMap<StateMap<TransitionCondition>> m_Transitions;

	friend TransitionCondition;
};