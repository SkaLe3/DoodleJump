#include "DoodleGameInstance.h"

void DoodleGameInstance::CreateSave()
{
    Serialize(m_HighScore);
    Serialize(m_LastScore);
    Serialize(m_HighPlatform);
    Serialize(m_LastPlatform);
    GameInstance::CreateSave();
}

void DoodleGameInstance::LoadSave()
{
    GameInstance::LoadSave();
    Deserialize(m_HighScore);
	Deserialize(m_LastScore);
    Deserialize(m_HighPlatform);
    Deserialize(m_LastPlatform);
}
