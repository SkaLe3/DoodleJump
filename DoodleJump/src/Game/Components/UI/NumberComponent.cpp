#include "NumberComponent.h"
#include "Components/SpriteComponent.h"
#include "Renderer/MySprite.h"
#include "Components/SceneComponent.h"
#include "World/World.h"
#include "World/Scene.h"

#include <string>

NumberComponent::NumberComponent()
{
	 digits.push_back(std::make_shared<MySprite>("assets/digits/0.png"));
	 digits.push_back(std::make_shared<MySprite>("assets/digits/1.png"));
	 digits.push_back(std::make_shared<MySprite>("assets/digits/2.png"));
	 digits.push_back(std::make_shared<MySprite>("assets/digits/3.png"));
	 digits.push_back(std::make_shared<MySprite>("assets/digits/4.png"));
	 digits.push_back(std::make_shared<MySprite>("assets/digits/5.png"));
	 digits.push_back(std::make_shared<MySprite>("assets/digits/6.png"));
	 digits.push_back(std::make_shared<MySprite>("assets/digits/7.png"));
	 digits.push_back(std::make_shared<MySprite>("assets/digits/8.png"));
	 digits.push_back(std::make_shared<MySprite>("assets/digits/9.png"));
	 digits.push_back(std::make_shared<MySprite>("assets/digits/empty.png"));
}

void NumberComponent::Start()
{
	for (auto& sprite : sprites)
		sprite->SetSprite(digits[10]);

	for (int i = 1; i < sprites.size(); i++)
	{
		sprites[i]->GetTransform().Translation.x = sprites[i]->GetTransform().Scale.x * i;
	}
}

void NumberComponent::Tick(double deltaTime)
{

}


void NumberComponent::Destroy()
{
	GetScene()->DestroyTickComponent(GetScene()->GetComponent(this));
	for (auto& sprite : sprites)
	{
		sprite->Destroy();
	}
}

void NumberComponent::Update(int32_t number)
{
	std::string num = std::to_string(number);
	size_t emptyAmount = sprites.size() - num.size();

	for (size_t i = 0; i < emptyAmount; i++)
	{
		sprites[i]->SetSprite(digits[10]);
	}
	for (size_t i = emptyAmount; i < sprites.size(); i++)
	{
		char digit = num[i - emptyAmount];
		int32_t ind = digit - '0';
		sprites[i]->SetSprite(digits[ind]);
	}
}

void NumberComponent::AddDigit(std::shared_ptr<SpriteComponent> sprite)
{
	sprites.push_back(sprite);
}

std::vector<std::shared_ptr<SpriteComponent>>& NumberComponent::GetSprites()
{
	return sprites;
}
