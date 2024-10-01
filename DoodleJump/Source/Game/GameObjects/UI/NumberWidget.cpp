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
	auto widget = GetScene()->GetObject(this);
	m_NumberComponent->SetOwner(widget);

	std::vector<std::shared_ptr<SpriteComponent>>& sprites = m_NumberComponent->GetSprites();
	for (auto& sprite : sprites)
	{
		sprite->SetOwner(widget);
		sprite->GetTransform().Scale = { 1.5, 1.5, 1.5 };
	}

	m_BoxComponent->SetCollisionEnabled(false);
	m_NumberComponent->Start();
}

void NumberWidget::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);

	Math::Vector camPos =  GetScene()->GetRenderCamera()->GetTransform().Translation;
	m_BoxComponent->GetTransform().Translation = { camPos.x + m_Coordinates.x, camPos.y + m_Coordinates.y, 0 };
}


void NumberWidget::Destroy()
{
	GameObject::Destroy();
	m_NumberComponent->Destroy();
}

void NumberWidget::Init(int32_t digits)
{
	std::shared_ptr<SpriteComponent> spriteComp;

	for (int i = 0; i < digits; i++)
	{
		spriteComp = CreateComponent<SpriteComponent>();
		spriteComp->SetupAttachment(GetBoxComponent());
		spriteComp->GetTransform().Translation.z = 2;
		m_NumberComponent->AddDigit(spriteComp);
	}
}

void NumberWidget::Update(int32_t number)
{
	m_NumberComponent->Update(number);
}

void NumberWidget::SetCoordinates(Math::Vector2D coords)
{
	m_Coordinates = coords;
}

std::shared_ptr<NumberComponent> NumberWidget::GetNumberComponent()
{
	return m_NumberComponent;
}

