#include "NumberWidget.h"
#include "Core/Components/SpriteComponent.h"
#include "Core/Components/CameraComponent.h"
#include "Components/UI/NumberComponent.h"

#include <vector>

NumberWidget::NumberWidget() : GameObject()
{
	m_NumberComponent = CreateComponent<NumberComponent>();
	OBJECT_LOG_CONSTRUCTOR()
}

NumberWidget::~NumberWidget()
{
	OBJECT_LOG_DESTRUCTOR()
}

void NumberWidget::Start()
{
	GameObject::Start();
	GetNumberComponent()->SetOwner(GetSelf());

	std::vector<std::shared_ptr<SpriteComponent>>& sprites = GetNumberComponent()->GetSprites();
	for (auto& sprite : sprites)
	{
		sprite->SetOwner(GetSelf());
		sprite->GetTransform().Scale = { 1.5, 1.5, 1.5 };
	}

	GetBoxComponent()->SetCollisionEnabled(false);
	GetNumberComponent()->Start();
}

void NumberWidget::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);

	Math::Vector camPos =  GetScene()->GetRenderCamera()->GetTransform().Translation;
	GetBoxComponent()->GetTransform().Translation = { camPos.x + m_Coordinates.x, camPos.y + m_Coordinates.y, 0 };
}


void NumberWidget::Destroy()
{
	GameObject::Destroy();
	GetNumberComponent()->Destroy();
}

void NumberWidget::Init(int32_t digits)
{
	std::shared_ptr<SpriteComponent> spriteComp;

	for (int i = 0; i < digits; i++)
	{
		spriteComp = CreateComponent<SpriteComponent>().lock();
		spriteComp->SetupAttachment(GetBoxComponent());
		spriteComp->GetTransform().Translation.z = 2;
		GetNumberComponent()->AddDigit(spriteComp);
	}
}

void NumberWidget::Update(int32_t number)
{
	GetNumberComponent()->Update(number);
}

void NumberWidget::SetCoordinates(Math::Vector2D coords)
{
	m_Coordinates = coords;
}

std::shared_ptr<NumberComponent> NumberWidget::GetNumberComponent()
{
	return m_NumberComponent.lock();
}

