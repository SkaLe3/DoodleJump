#pragma once
#include "Core/Base/GameInstance.h"

class DoodleGameInstance : public GameInstance
{
public:
	//~ Begin GameInstance Interface
	//virtual void Init(const string& filename) override;
	//virtual void Shutdown() override;
	virtual void CreateSave() override;
	virtual void LoadSave() override;
	//~ End GameInstance Interface

	inline double GetHighScore() { return m_HighScore; }
	inline double GetLastScore() { return m_LastScore; }
	inline double GetHighestReachedPlatform() { return m_HighPlatform; }
	inline double GetLastPassedPlatform() { return m_LastPlatform; }

	inline void SetHighScore(double highScore) { m_HighScore = highScore; }
	inline void SetLastScore(double lastScore) { m_LastScore = lastScore; }
	inline void SetHighestReachedPlatform(double highPlatform) { m_HighPlatform = highPlatform; }
	inline void SetLastPassedPlatform(double lastPlatform) { m_LastPlatform = lastPlatform; }

private:
	double m_HighScore = 0;
	double m_LastScore = 0;
	double m_HighPlatform = 0;
	double m_LastPlatform = 0;
};
