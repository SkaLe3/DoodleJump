#include "MenuBackground.h"
#include "Core/Base/AssetManager.h"



MenuBackground::MenuBackground() : Background()
{
	m_SpriteComponent->SetSprite(AssetManager::Get().GetAsset<MySprite>("S_MenuBackground"));
}
