#include "MenuBackground.h"
#include "Core/Base/AssetManager.h"



MenuBackground::MenuBackground() : Background()
{
	GetSpriteComponent()->SetSprite(AssetManager::Get().GetAsset<MySprite>("S_MenuBackground"));
	GetSpriteComponent()->GetTransform().Scale = { 36, 54, 1 };
}
