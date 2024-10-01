#include "LevelBackground.h"
#include "Core/Base/AssetManager.h"



LevelBackground::LevelBackground() : Background()
{
	GetSpriteComponent()->SetSprite(AssetManager::Get().GetAsset<MySprite>("S_UnderwaterBackground"));
}
