#include "GameInstance.h"
#include "Core/Base/Log.h"
#include <fstream>

GameInstance* GameInstance::s_Instance = nullptr;


GameInstance& GameInstance::Get()
{
	return *s_Instance;
}

GameInstance::GameInstance()
{
	s_Instance = this;
}

GameInstance::~GameInstance()
{
	s_Instance = nullptr;
}

void GameInstance::Init(const std::string& filename)
{
	m_Filename = filename;
}

void GameInstance::Shutdown()
{

}

void GameInstance::CreateSave()
{
	std::ofstream saveFile(m_SaveDirectory / m_Filename);

	if (saveFile.is_open())
	{
		LOG("Can't open file to save game: " + m_SaveDirectory.string() + m_Filename);
	}

	saveFile << 15 << " " << 30 << std::endl;

	
	saveFile.close();

}

void GameInstance::LoadSave()
{
	std::ifstream saveFile(m_SaveDirectory / m_Filename);
	if (saveFile.is_open())
	{
		LOG("Can't open save file: " + m_SaveDirectory.string() + m_Filename);
	}
	double fi;
	double se;
	saveFile >> fi >> se;

	saveFile.close();
}
