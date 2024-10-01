#include "SpriteWidget.h"
#include "Core/Components/SpriteComponent.h"
#include "Core/Components/CameraComponent.h"
#include "Core/Base/Log.h"

SpriteWidget::SpriteWidget() : GameObject()
{
	m_SpriteComponent = CreateComponent<SpriteComponent>();
	GetSprite()->SetupAttachment(GetBoxComponent());
	OBJECT_LOG_CONSTRUCTOR()
}

SpriteWidget::~SpriteWidget()
{
	OBJECT_LOG_DESTRUCTOR()
}

void SpriteWidget::Start()
{
	GameObject::Start();
	GetSprite()->SetOwner(GetSelf());

	GetBoxComponent()->SetCollisionEnabled(false);
}

void SpriteWidget::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);

	Math::Vector camPos = GetScene()->GetRenderCamera()->GetTransform().Translation;
	GetBoxComponent()->GetTransform().Translation = { camPos.x + m_Coordinates.x, camPos.y + m_Coordinates.y, 0 };
}

void SpriteWidget::Destroy()
{
	GameObject::Destroy();
	GetSprite()->Destroy();
}

void SpriteWidget::SetCoordinates(Math::Vector2D coords)
{
	m_Coordinates = coords;
}

std::shared_ptr<SpriteComponent> SpriteWidget::GetSprite()
{
	return m_SpriteComponent.lock();
}
