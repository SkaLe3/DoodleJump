#pragma once
#include <string>
#include <filesystem>

class GameInstance
{
public:
	static GameInstance& Get();
public:
	GameInstance();
	virtual ~GameInstance();

	virtual void Init(const std::string& filename);
	virtual void Shutdown();
	virtual void CreateSave();
	virtual void LoadSave();

private:
	static GameInstance* s_Instance;

protected:
	std::string m_Filename;

private:
	const std::filesystem::path m_SaveDirectory = "Saved";
};