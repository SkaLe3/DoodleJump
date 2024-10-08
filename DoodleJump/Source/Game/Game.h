#pragma once
#include "Core/MyFramework.h"
#include "Core/Base/AssetManager.h"
#include "DoodleGameInstance.h"

class Game : public MyFramework
{
public:
	Game(uint32_t w, uint32_t h, bool fs, const std::string& contentDirectory);

public:
	//~Begin Framework Interface
	virtual bool Init();
	virtual void Close();
	//~End Framework Interface

	AssetManager* m_AssetManager;
	DoodleGameInstance* m_GameInstance;
	std::string m_ContentDirectory;
};