#pragma once
#include "Core/Base/GameInstance.h"

class DoodleGameInstance : public GameInstance
{
public:
	//~ Begin GameInstance Interface
	//virtual void Init(const string& filename) override;
	//virtual void Shutdown() override;
	//virtual void CreateSave() override;
	//virtual void LoadSave() override;
	//~ End GameInstance Interface

	inline double GetBestScore() { return m_BestScore; }
	inline double GetLastScore() { return m_LastScore; }

	inline void SetBestScore(double bestScore) { m_BestScore = bestScore; }
	inline void SetLastScore(double lastScore) { m_LastScore = lastScore; }

private:
	double m_BestScore = 0;
	double m_LastScore = 0;
};
