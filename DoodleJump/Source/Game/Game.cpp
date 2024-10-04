#include "Game.h"
#include "Core/Base/AssetManager.h"


Game::Game(uint32_t w, uint32_t h, bool fs, const std::string& contentDirectory)
	: MyFramework(w, h, fs),  m_ContentDirectory(contentDirectory)
{

}

bool Game::Init()
{
	m_AssetManager = new AssetManager(m_ContentDirectory);
	m_AssetManager->Init();
	
	m_GameInstance = new DoodleGameInstance();
	m_GameInstance->Init("DoodleSave.save");
	m_GameInstance->LoadSave();

	MyFramework::Init();
	return true;
}

void Game::Close()
{
	m_GameInstance->CreateSave();
	m_GameInstance->Shutdown();
	MyFramework::Close();
	delete m_AssetManager;
	delete m_GameInstance;
}

