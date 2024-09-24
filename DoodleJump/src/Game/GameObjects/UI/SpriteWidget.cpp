#include "SpriteWidget.h"
#include "Components/SpriteComponent.h"
#include "Components/CameraComponent.h"
#include "Core/Base/Log.h"

SpriteWidget::SpriteWidget() : GameObject()
{
	spriteComponent = CreateComponent<SpriteComponent>();
	spriteComponent->SetupAttachment(GetBoxComponent());
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
	spriteComponent->SetOwner(widget);

	boxComponent->SetCollisionEnabled(false);

}

void SpriteWidget::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);

	Math::Vector camPos = GetScene()->GetRenderCamera()->GetTransform().Translation;

	boxComponent->GetTransform().Translation = { camPos.x + coordinates.x, camPos.y + coordinates.y, 0 };
}

void SpriteWidget::Destroy()
{
	GameObject::Destroy();
	spriteComponent->Destroy();
}

void SpriteWidget::SetCoordinates(Math::Vector2D coords)
{
	coordinates = coords;
}

std::shared_ptr<SpriteComponent> SpriteWidget::GetSprite()
{
	return spriteComponent;
}
