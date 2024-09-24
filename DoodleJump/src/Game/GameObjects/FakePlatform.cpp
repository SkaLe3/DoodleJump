#include "FakePlatform.h"

FakePlatform::FakePlatform() : Platform()
{
	spriteComponent->GetTransform().Scale = { 6, 2.95, 1 };
	spriteComponent->GetTransform().Translation.z = -0.5;
	spriteComponent->GetTransform().Translation.y = -0.3;
	boxComponent->SetHalfSize({ 2.7, 0.5 });
}

void FakePlatform::Start()
{
	Platform::Start();

	boxComponent->OnBeginOverlap.Add(std::bind(&FakePlatform::OnCollision, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void FakePlatform::Tick(double deltaTime)
{
	Platform::Tick(deltaTime);
	if (!bBroken)
		return;
	if (timer >= 0.32)
	{
		bBroken = false;
		boxComponent->GetTransform().Translation.y = -10;
		spriteComponent->SwitchAnimationState("idle");
		timer = 0;

	}
	timer += deltaTime;

}


void FakePlatform::OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime)
{
	std::string otherTag = otherObject->GetTag();
	if (normal.y < 0 && otherTag == "doodle")
	{
		Break();
	}

}

void FakePlatform::Break()
{
	spriteComponent->SwitchAnimationState("break");
	bBroken = true;
}
