#pragma once
#include "Core/Base/Log.h"
#include "Asset.h"

#include <unordered_map>

class MySprite;
class Animation;

class AssetManager
{
public:
	static AssetManager& Get();
public:
	AssetManager(std::filesystem::path contentPath);
	virtual ~AssetManager();

	virtual void Init();
	template<typename T>
	std::shared_ptr<T> GetAsset(const std::string& assetName)
	{
		LOG("GetAsset<T> should be specialized for each type")
	}		

	template<>
	std::shared_ptr<MySprite> GetAsset<MySprite>(const std::string& assetName)
	{
		if (m_AssetMap.count(assetName))
		{
			return std::static_pointer_cast<MySprite>(std::static_pointer_cast<SpriteAsset>(m_AssetMap[assetName])->GetSprite());
		}
		else
		{
			LOG("Failed to retrieve asset: " + assetName);
		}
		return nullptr;
	}
	template<>
	std::shared_ptr<Animation> GetAsset<Animation>(const std::string& assetName)
	{
		if (m_AssetMap.count(assetName))
		{
			return std::static_pointer_cast<Animation>(std::static_pointer_cast<AnimationAsset>(m_AssetMap[assetName])->GetAnimation());
		}
		else
		{
			LOG("Failed to retrieve asset: " + assetName);
		}
		return nullptr;
	}

	/* Debug functions */
	std::unordered_map<std::string, std::shared_ptr<Asset>>& GetMap() {return m_AssetMap;}
	inline std::filesystem::path GetContentPath() { return m_ContentPath; }

private:
	/* Function to get raw asset instance */
	std::shared_ptr<SpriteAsset> GetSpriteAsset(const std::string& assetName);
private:
	static AssetManager* s_Instance;
	std::filesystem::path m_ContentPath;

	std::unordered_map<std::string, std::shared_ptr<Asset>> m_AssetMap;
};