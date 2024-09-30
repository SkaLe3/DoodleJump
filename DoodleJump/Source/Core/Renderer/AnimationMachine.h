#pragma once
#include "AnimationState.h"
#include "Animation.h"

#include <string>
#include <unordered_map>


class AnimationMachine
{
public:
	static std::shared_ptr<AnimationMachine> Create();

public:
	void Update(double deltaTime);

	void CreateState(const std::string& key, double frameDuration);
	void SwitchState(const std::string& key);
	void SetStateAnimation(const std::string& state, std::shared_ptr<Animation>);

	inline std::shared_ptr<MySprite> GetActiveFrame() { return  GetActive()->GetFrame(); }
	inline double GetActiveStateDuration() { return GetActive()->GetAnimationDuration(); } // check
	inline std::string GetActiveName() { return m_ActiveStateName; }
	inline bool IsValidState(const std::string& state) { return (bool)m_States.count(state); }
	void SetEntryState(const std::string& key);


private:
	/* No check required since m_ActiveStateName is always valid */
	inline std::shared_ptr<AnimationState> GetActive() { return m_States[m_ActiveStateName]; }
	void SetActive(const std::string& state);
private:
	using AnimationMachineMap = std::unordered_map<std::string, std::shared_ptr<AnimationState>>;

	AnimationMachineMap m_States;
	std::string m_ActiveStateName;
	std::shared_ptr<MySprite> m_ActiveFrame;
	std::string m_EntryStateName;

};

