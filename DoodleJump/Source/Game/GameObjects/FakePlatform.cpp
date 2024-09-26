#include "FakePlatform.h"
#include <memory>

FakePlatform::FakePlatform() : Platform()
{
	spriteComponent->GetTransform().Scale = { 6, 2.95, 1 };
	spriteComponent->GetTransform().Translation.z = -0.5;
	spriteComponent->GetTransform().Translation.y = -0.3;
	boxComponent->SetHalfSize({ 2.7, 0.5 });

	// Asset Manager should be implemented to avoid multiple loading of the same images
	std::shared_ptr<MySprite> fpFrame1 = std::make_shared<MySprite>("assets2/fake-platform-1.png");
	std::shared_ptr<MySprite> fpFrame2 = std::make_shared<MySprite>("assets2/fake-platform-2.png");
	std::shared_ptr<MySprite> fpFrame3 = std::make_shared<MySprite>("assets2/fake-platform-3.png");
	std::shared_ptr<MySprite> fpFrame4 = std::make_shared<MySprite>("assets2/fake-platform-4.png");

	std::shared_ptr<AnimationMachine> animMachine = AnimationMachine::Create();
	animMachine->CreateState("break", 0.08);
	animMachine->CreateState("idle", -1);
	animMachine->AddFrame("break", fpFrame1);
	animMachine->AddFrame("break", fpFrame2);
	animMachine->AddFrame("break", fpFrame3);
	animMachine->AddFrame("break", fpFrame4);
	animMachine->AddFrame("idle", fpFrame1);
	animMachine->SetEntryState("idle");
	GetSprite()->SetAnimationMachine(animMachine);
	GetSprite()->EnableAnimation();
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
