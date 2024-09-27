#include "AssetManager.h"
#include "Asset.h"

namespace fs = std::filesystem;

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
	for (const auto& entry : fs::directory_iterator(m_ContentPath))
	{
		if (fs::path entryPath = entry.path(); fs::is_regular_file(entryPath) )
		{
			if (entryPath.extension() == ".png")
			{
				m_AssetMap["S_" + entryPath.stem().string()] = Asset::Create<SpriteAsset>(entryPath);
			}
		}
	}
}

AssetManager& AssetManager::Get()
{
	return *s_Instance;
}

