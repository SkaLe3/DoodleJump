#include "NumberComponent.h"
#include "Components/SpriteComponent.h"
#include "Renderer/MySprite.h"
#include "Components/SceneComponent.h"
#include "World/World.h"
#include "World/Scene.h"

#include <string>

NumberComponent::NumberComponent()
{
	m_Digits.push_back(std::make_shared<MySprite>("assets2/digits/0.png"));
	m_Digits.push_back(std::make_shared<MySprite>("assets2/digits/1.png"));
	m_Digits.push_back(std::make_shared<MySprite>("assets2/digits/2.png"));
	m_Digits.push_back(std::make_shared<MySprite>("assets2/digits/3.png"));
	m_Digits.push_back(std::make_shared<MySprite>("assets2/digits/4.png"));
	m_Digits.push_back(std::make_shared<MySprite>("assets2/digits/5.png"));
	m_Digits.push_back(std::make_shared<MySprite>("assets2/digits/6.png"));
	m_Digits.push_back(std::make_shared<MySprite>("assets2/digits/7.png"));
	m_Digits.push_back(std::make_shared<MySprite>("assets2/digits/8.png"));
	m_Digits.push_back(std::make_shared<MySprite>("assets2/digits/9.png"));
	m_Digits.push_back(std::make_shared<MySprite>("assets2/digits/empty.png"));
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
