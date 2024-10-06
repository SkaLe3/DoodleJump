#include "Game.h"
#include "Core/Base/AssetManager.h"


Game::Game(uint32_t w, uint32_t h, bool fs, const std::string& contentDirectory)
	: MyFramework(w, h, fs, contentDirectory)
{

}

bool Game::Init()
{
	// TODO: Now Create called from derived class. Move it to the base class and specify only type in derived
	CreateGameInstance<DoodleGameInstance>();

	m_AssetManager->Init();
	
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

}

