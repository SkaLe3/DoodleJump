#include "SpriteWidget.h"
#include "Components/SpriteComponent.h"
#include "Components/CameraComponent.h"
#include "Core/Base/Log.h"

SpriteWidget::SpriteWidget() : GameObject()
{
	m_SpriteComponent = CreateComponent<SpriteComponent>();
	m_SpriteComponent->SetupAttachment(GetBoxComponent());
	OBJECT_LOG_CONSTRUCTOR()
}

SpriteWidget::~SpriteWidget()
{
	OBJECT_LOG_DESTRUCTOR()
}

void SpriteWidget::Start()
{
	GameObject::Start();
	auto widget = GetScene()->GetObject(this);
	m_SpriteComponent->SetOwner(widget);

	m_BoxComponent->SetCollisionEnabled(false);
}

void SpriteWidget::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);

	Math::Vector camPos = GetScene()->GetRenderCamera()->GetTransform().Translation;
	m_BoxComponent->GetTransform().Translation = { camPos.x + m_Coordinates.x, camPos.y + m_Coordinates.y, 0 };
}

void SpriteWidget::Destroy()
{
	GameObject::Destroy();
	m_SpriteComponent->Destroy();
}

void SpriteWidget::SetCoordinates(Math::Vector2D coords)
{
	m_Coordinates = coords;
}

std::shared_ptr<SpriteComponent> SpriteWidget::GetSprite()
{
	return m_SpriteComponent;
}
