#pragma once
#include "Renderer/MySprite.h"
#include "Renderer/Animation.h"

#include <filesystem>
#include <vector>
#include <memory>

class Asset
{
public:
	template<typename T, typename U>
	static std::shared_ptr<T> Create(U assetSource) { return std::make_shared<T>(assetSource); }

public:
	virtual ~Asset() {}
	virtual std::shared_ptr<void> Get() = 0;
};



class SpriteAsset : public Asset
{
public:
	SpriteAsset(std::filesystem::path assetPath);

	//~ Begin Asset Interface
	virtual std::shared_ptr<void> Get() override { return m_SpriteRef; }
	//~ End Asset Interface

	std::shared_ptr<MySprite> GetSprite() { return m_SpriteRef; }

private:
	std::shared_ptr<MySprite> m_SpriteRef;
};



class AnimationAsset : public Asset
{
public:
	AnimationAsset(std::vector<std::shared_ptr<SpriteAsset>> animationSource);

	//~ Begin Asset Interface
	virtual std::shared_ptr<void> Get() override { return m_AnimationRef; }
	//~ End Asset Interface

	std::shared_ptr<Animation> GetAnimation() { return m_AnimationRef; }

private:
	std::shared_ptr<Animation> m_AnimationRef;
};
