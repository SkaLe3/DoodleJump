#include "NumberWidget.h"
#include "Components/UI/NumberComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/CameraComponent.h"
#include "Math/Vector.h"
#include <vector>

NumberWidget::NumberWidget() : GameObject()
{
	numberComponent = CreateComponent<NumberComponent>();
	OBJECT_LOG_CONSTRUCTOR()
}

NumberWidget::~NumberWidget()
{
	OBJECT_LOG_DESTRUCTOR()
}

void NumberWidget::Start()
{
	GameObject::Start();
	auto widget = GetScene()->GetObject(this);
	numberComponent->SetOwner(widget);

	std::vector<std::shared_ptr<SpriteComponent>>& sprites = numberComponent->GetSprites();
	for (auto& sprite : sprites)
	{
		sprite->SetOwner(widget);
		sprite->GetTransform().Scale = { 1.5, 1.5, 1.5 };
	}

	boxComponent->SetCollisionEnabled(false);
	numberComponent->Start();
}

void NumberWidget::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);

	Math::Vector camPos =  GetScene()->GetRenderCamera()->GetTransform().Translation;

	boxComponent->GetTransform().Translation = { camPos.x + coordinates.x, camPos.y + coordinates.y, 0 };
}


void NumberWidget::Destroy()
{
	GameObject::Destroy();
	numberComponent->Destroy();
}

void NumberWidget::Init(int32_t digits)
{
	std::shared_ptr<SpriteComponent> spriteComp;

	for (int i = 0; i < digits; i++)
	{
		spriteComp = CreateComponent<SpriteComponent>();
		spriteComp->SetupAttachment(GetBoxComponent());
		spriteComp->GetTransform().Translation.z = 2;
		numberComponent->AddDigit(spriteComp);
	}
}

void NumberWidget::Update(int32_t number)
{
	numberComponent->Update(number);
}

void NumberWidget::SetCoordinates(Math::Vector2D coords)
{
	coordinates = coords;
}

std::shared_ptr<NumberComponent> NumberWidget::GetNumberComponent()
{
	return numberComponent;
}

