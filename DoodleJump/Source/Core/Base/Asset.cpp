#include "Asset.h"


SpriteAsset::SpriteAsset(std::filesystem::path assetPath)
{
	m_SpriteRef = std::make_shared<MySprite>( assetPath.string().c_str());
}

AnimationAsset::AnimationAsset(const std::vector<std::shared_ptr<SpriteAsset>>& animationSource)
{
	std::vector<std::shared_ptr<MySprite>> newAnimSource;
	for (auto& asset : animationSource)
	{
		newAnimSource.push_back(asset->GetSprite())	;
	}

	m_AnimationRef = std::make_shared<Animation>(newAnimSource);
}

