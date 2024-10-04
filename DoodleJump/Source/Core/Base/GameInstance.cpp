#include "GameInstance.h"
#include "Core/Base/Log.h"
#include <fstream>


unsigned char ComputeXORChecksum(const std::string& data)
{
	unsigned char checksum = 0;
	for (char c : data)
	{
		checksum ^= c;
	}
	return checksum;
}


GameInstance* GameInstance::s_Instance = nullptr;

const static std::string ENCYPTION_KEY = "encryption_test";

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

	std::string saveData = m_OutData.str();
	unsigned char checksum = ComputeXORChecksum(saveData);
	std::string encryptedData = Encrypt(saveData);

	

	saveFile << encryptedData << std::endl;
	saveFile << static_cast<int>(checksum) << std::endl;
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
	std::string encryptedData;
	int savedChecksum;
	std::getline(saveFile, encryptedData);
	saveFile >> savedChecksum;
	saveFile.close();

	std::string decryptedData = Decrypt(encryptedData);
	unsigned char recalculatedChecksum = ComputeXORChecksum(decryptedData);


	if (static_cast<int>(recalculatedChecksum) != savedChecksum)
	{
		LOG("Data integrity check failed! Save file may have been tampered with.");
		m_InData << "";
		return;
	}
	m_InData.str(decryptedData);
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

std::string GameInstance::Encrypt(const std::string& data)
{
	std::string encrypted = data;
	for (size_t i = 0; i < data.size(); i++)
	{
		encrypted[i] ^= ENCYPTION_KEY[i % ENCYPTION_KEY.size()];
	}
	return encrypted;
}

std::string GameInstance::Decrypt(const std::string& data)
{
	return Encrypt(data);
}
