#include "Platform.h"
#include "Core/Base/Log.h"
#include "Core/Base/AssetManager.h"

#include "Components/ProjectileMovementComponent.h"

#include <cstdlib>
#include <ctime>

Platform::Platform() : GameObject()
{
	m_SpriteComponent = CreateComponent<SpriteComponent>();
	auto sprite = GetSpriteComponent();
	sprite->SetupAttachment(GetBoxComponent());

	sprite->GetTransform().Scale = { 6.68, 6.68, 1 };
	sprite->GetTransform().Translation.z = -0.5;
	sprite->GetTransform().Translation.y = 0.7;
	sprite->SetSprite(AssetManager::Get().GetAsset<MySprite>("S_Bamboo"));
	auto box = GetBoxComponent();
	box->SetHalfSize({ 2.7, 0.5 });
	box->SetCollisionChannel(ECollisionChannel::WorldDynamic);
	box->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Ignore);
	box->SetCollisionResponce(ECollisionChannel::WorldStatic, ECollisionResponse::Overlap);

	m_MovementComponent = CreateComponent<ProjectileMovementComponent>();

	OBJECT_LOG_CONSTRUCTOR()
}

Platform::~Platform()
{
	OBJECT_LOG_DESTRUCTOR()
}

void Platform::Start()
{
	GameObject::Start();
	GetSpriteComponent()->SetOwner(GetSelf());

	auto movement = GetMovementComponent();
	movement->SetOwner(GetSelf());
	movement->SetGravity(0);
	GetBoxComponent()->OnBeginOverlap.Add(std::bind(&Platform::OnCollision,
													this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

}

void Platform::Tick(double deltaTime)
{
	GameObject::Tick(deltaTime);
}

void Platform::Destroy()
{
	GameObject::Destroy();
	GetSpriteComponent()->Destroy();
}

void Platform::Pass()
{
	m_bPassed = true;
}

bool Platform::IsPassed()
{
	return m_bPassed;
}

void Platform::Reset()
{
	m_bPassed = false;
	StopMovement();
}

void Platform::StartMovement()
{
	srand(time(NULL));
	int randomValue = (rand() % 2) == 0 ? -1 : 1;
	Math::Vector2D direction = { 1, 0 };
	GetMovementComponent()->SetInitialVelocity(direction * randomValue * m_MoveSpeed);
}

void Platform::StopMovement()
{
	GetMovementComponent()->SetVelocity({ 0, 0 });
}

void Platform::ReflectMovement()
{
	Math::Vector2D velocity = GetMovementComponent()->GetVelocity();
	velocity.x = -velocity.x;
	GetMovementComponent()->SetVelocity(velocity);
}

void Platform::OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime)
{
	std::string otherTag = otherObject->GetTag();
	if (otherTag == "left wall" || otherTag == "right wall")
	{
		ReflectMovement();
	}
}
