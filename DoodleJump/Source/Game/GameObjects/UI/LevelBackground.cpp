#include "LevelBackground.h"
#include "Core/Base/AssetManager.h"



LevelBackground::LevelBackground() : Background()
{
	m_SpriteComponent->SetSprite(AssetManager::Get().GetAsset<MySprite>("S_UnderwaterBackground"));
}
