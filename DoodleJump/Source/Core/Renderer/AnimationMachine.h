#pragma once
#include "AnimationState.h"

#include <string>
#include <unordered_map>

			 
// TODO: Create Animation class and handle it as asset. Create instance of animation and store in AnimationState
// TODO: Create AnimationSystem class to contain AnimationMachine
// TODO: Add states transitions conditions




class AnimationMachine
{
public:
	static std::shared_ptr<AnimationMachine> Create();

public:
	void Update(double deltaTime);

	void CreateState(const std::string& key, double frameDuration);
	void SwitchState(const std::string& key);
	void AddFrame(const std::string& state, std::shared_ptr<MySprite> frame);

	inline std::shared_ptr<MySprite> GetActiveFrame()	{ return  m_ActiveState->GetFrame(); }
	inline double GetActiveStateDuration() { return m_ActiveState->GetStateDuration();}
	
	void SetEntryState(const std::string& key);

private:
	using AnimationMachineMap = std::unordered_map<std::string, std::shared_ptr<AnimationState>>;

	AnimationMachineMap m_States;
	std::shared_ptr<AnimationState> m_ActiveState;
	std::shared_ptr<MySprite> m_ActiveFrame;
	std::string m_EntryStateKey;
	double m_ElapsedTime = 0;
};

