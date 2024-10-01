#include "AssetManager.h"

#include <fstream>

namespace fs = std::filesystem;

std::shared_ptr<SpriteAsset> AssetManager::GetSpriteAsset(const std::string& assetName)
{
	if (m_AssetMap.count(assetName))
	{
		return std::static_pointer_cast<SpriteAsset>(m_AssetMap[assetName]);
	}
	else
	{
		LOG("Failed to retrieve asset: " + assetName);
	}
	return nullptr;
}

AssetManager* AssetManager::s_Instance = nullptr;

AssetManager::AssetManager(fs::path contentPath) : m_ContentPath(contentPath)
{
	s_Instance = this;
}

AssetManager::~AssetManager()
{
	s_Instance = nullptr;
}

void AssetManager::Init()
{
	for (const auto& entry : fs::recursive_directory_iterator(m_ContentPath))
	{
		if (fs::path entryPath = entry.path(); fs::is_regular_file(entryPath))
		{
			if (entryPath.extension() == ".png")
			{
				m_AssetMap["S_" + entryPath.stem().string()] = Asset::Create<SpriteAsset>(entryPath);
			}
		}
	}
	for (const auto& entry : fs::recursive_directory_iterator(m_ContentPath))
	{
		if (fs::path entryPath = entry.path(); fs::is_regular_file(entryPath))
		{
			if (entryPath.extension() == ".sklanim")
			{
				std::ifstream animFile(entryPath.string());
				std::vector<std::shared_ptr<SpriteAsset>> frames;
				std::string line;
				if (animFile.is_open())
				{
					while (std::getline(animFile, line))
					{
						if (!line.empty())
						{
							if (m_AssetMap.count(line))
								frames.push_back(GetSpriteAsset(line));
							else
								LOG("Unvalid animation frame referenced in animation file: " + entryPath.string());
						}
					}
					animFile.close();
				}
				else
				{
					LOG("Unable to open file: " + entryPath.string());
				}
				m_AssetMap["A_" + entryPath.stem().string()] = Asset::Create<AnimationAsset>(frames);
			}
		}
	}
}

AssetManager& AssetManager::Get()
{
	return *s_Instance;
}

