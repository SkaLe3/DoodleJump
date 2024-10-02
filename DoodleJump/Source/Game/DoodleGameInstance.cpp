#include "DoodleGameInstance.h"

void DoodleGameInstance::CreateSave()
{
    Serialize(m_HighScore);
    Serialize(m_LastScore);
    GameInstance::CreateSave();
}

void DoodleGameInstance::LoadSave()
{
    GameInstance::LoadSave();
    Deserialize(m_HighScore);
	Deserialize(m_LastScore);
}
