#pragma once
#include "MySprite.h"

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>

			 
// TODO: Create Animation class and handle it as asset. Create instance of animation and store in AnimationState
// TODO: Create AnimationSystem class to contain AnimationMachine
// TODO: Add states transitions conditions

class AnimationState;

class AnimationState
{
public:
	/* Resets frame index*/
	inline void Reset() { m_Index = 0; }

	inline std::shared_ptr<MySprite> GetFrame() { return m_State[m_Index]; }
	inline double GetStateDuration() { return m_State.size() * m_FrameDuration; }
	inline double GetFrameDuration() { return m_FrameDuration; }
	
	inline void AddFrame(std::shared_ptr<MySprite> frame) { m_State.push_back(frame); }
	inline void NextFrame() { m_Index = ++m_Index % m_State.size(); }

	void SetFrameDuration(double frameDuration);

private:
	using AnimationStateVec = std::vector<std::shared_ptr<MySprite>>;

	AnimationStateVec m_State;
	double m_FrameDuration;
	size_t m_Index = 0;
};


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
	
	void SetEntryState(const std::string& key);

private:
	using AnimationMachineMap = std::unordered_map<std::string, std::shared_ptr<AnimationState>>;

	AnimationMachineMap m_States;
	std::shared_ptr<AnimationState> m_ActiveState;
	std::shared_ptr<MySprite> m_ActiveFrame;
	std::string m_EntryStateKey;
	double m_ElapsedTime = 0;
};

