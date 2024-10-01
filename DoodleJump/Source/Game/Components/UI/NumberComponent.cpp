#include "NumberComponent.h"
#include "Core/Base/AssetManager.h"
#include "Core/Components/SpriteComponent.h"
#include "Core/Components/SceneComponent.h"
#include "Core/Renderer/MySprite.h"
#include "Core/World/World.h"

#include <string>

NumberComponent::NumberComponent()
{
	m_Digits.push_back(AssetManager::Get().GetAsset<MySprite>("S_0"));
	m_Digits.push_back(	AssetManager::Get().GetAsset<MySprite>("S_1"));
	m_Digits.push_back(	AssetManager::Get().GetAsset<MySprite>("S_2"));
	m_Digits.push_back(	AssetManager::Get().GetAsset<MySprite>("S_3"));
	m_Digits.push_back(	AssetManager::Get().GetAsset<MySprite>("S_4"));
	m_Digits.push_back(	AssetManager::Get().GetAsset<MySprite>("S_5"));
	m_Digits.push_back(	AssetManager::Get().GetAsset<MySprite>("S_6"));
	m_Digits.push_back(	AssetManager::Get().GetAsset<MySprite>("S_7"));
	m_Digits.push_back(	AssetManager::Get().GetAsset<MySprite>("S_8"));
	m_Digits.push_back(	AssetManager::Get().GetAsset<MySprite>("S_9"));
	m_Digits.push_back(AssetManager::Get().GetAsset<MySprite>("S_Empty"));
}

void NumberComponent::Start()
{
	for (auto& sprite : m_Sprites)
		sprite->SetSprite(m_Digits[10]);

	for (int i = 1; i < m_Sprites.size(); i++)
	{
		m_Sprites[i]->GetTransform().Translation.x = m_Sprites[i]->GetTransform().Scale.x * i;
	}
}

void NumberComponent::Tick(double deltaTime)
{

}


void NumberComponent::Destroy()
{
	GetScene()->DestroyTickComponent(GetScene()->GetComponent(this));
	for (auto& sprite : m_Sprites)
	{
		sprite->Destroy();
	}
}

void NumberComponent::Update(int32_t number)
{
	std::string num = std::to_string(number);
	size_t emptyAmount = m_Sprites.size() - num.size();

	for (size_t i = 0; i < emptyAmount; i++)
	{
		m_Sprites[i]->SetSprite(m_Digits[10]);
	}
	for (size_t i = emptyAmount; i < m_Sprites.size(); i++)
	{
		char digit = num[i - emptyAmount];
		int32_t ind = digit - '0';
		m_Sprites[i]->SetSprite(m_Digits[ind]);
	}
}

void NumberComponent::AddDigit(std::shared_ptr<SpriteComponent> sprite)
{
	m_Sprites.push_back(sprite);
}

std::vector<std::shared_ptr<SpriteComponent>>& NumberComponent::GetSprites()
{
	return m_Sprites;
}
