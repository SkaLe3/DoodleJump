#include "GameInstance.h"
#include "Core/Base/Log.h"
#include <fstream>

GameInstance* GameInstance::s_Instance = nullptr;



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

	if (!saveFile.is_open())
	{
		LOG("Can't open file to save game: " + m_SaveDirectory.string() + m_Filename);
		return;
	}

	saveFile << m_OutData.str();
	saveFile.close();
}

void GameInstance::LoadSave()
{
	std::ifstream saveFile(m_SaveDirectory / m_Filename);
	if (!saveFile.is_open())
	{
		LOG("Can't open save file: " + m_SaveDirectory.string() + m_Filename);
		return;
	}
	m_InData << saveFile.rdbuf();
	saveFile.close();
}


void GameInstance::Serialize(double value)
{
	m_OutData << value << std::endl;
}

void GameInstance::Serialize(const std::string& value)
{
	m_OutData << value << std::endl;
}

void GameInstance::Deserialize(double& value)
{
	if (!m_InData.str().empty())
	{
		m_InData >> value;
	}
	else
	{
		LOG("Failed to deserialize double value");
	}
}

void GameInstance::Deserialize(std::string& value)
{
	if (!m_InData.str().empty())
	{
		m_InData >> value;
	}
	else
	{
		LOG("Failed to deserialize string value");
	}
}
