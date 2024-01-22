#include "NumberComponent.h"
#include "Components/SpriteComponent.h"
#include "Renderer/MySprite.h"

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

}

void NumberComponent::Tick(double DeltaTime)
{

}
