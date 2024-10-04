#pragma once
#include <string>
#include <filesystem> 
#include <sstream>
#include <unordered_map>

class GameInstance
{
public:
	template<typename T>
	static T& Get() { return *(static_cast<T*>(s_Instance)); }
public:
	GameInstance();
	virtual ~GameInstance();

	virtual void Init(const std::string& filename);
	virtual void Shutdown();
	virtual void CreateSave();
	virtual void LoadSave();

protected:
	void Serialize(double value);
	void Serialize(const std::string& value);
	void Deserialize(double& value);
	void Deserialize(std::string& value);

private:
	std::string Encrypt(const std::string& data);
	std::string Decrypt(const std::string& data);

private:
	static GameInstance* s_Instance;

protected:
	std::string m_Filename;

private:
	const std::filesystem::path m_SaveDirectory = "Saved";
	std::stringstream m_InData;
	std::stringstream m_OutData;


};