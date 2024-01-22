#include "Monster.h"
#include "DJGameMode.h"
#include "Doodle.h"

#include <string>

Monster::Monster()
{
	spriteComponent = CreateComponent<SpriteComponent>();
	spriteComponent->SetupAttachment(GetBoxComponent());

	std::shared_ptr<MySprite> spriteRef = std::make_shared<MySprite>("assets/monster.png");
	spriteComponent->SetSprite(spriteRef);

	boxComponent->SetHalfSize({ 3, 2.73 });
}

void Monster::Start()
{
	GameObject::Start();
	auto monster = GetScene()->GetObject(this);
	spriteComponent->SetOwner(monster);

	spriteComponent->GetTransform().Scale = { 8, 5.455, 1.0 };
	spriteComponent->GetTransform().Translation = { 0.0, 0.0, 0.0 };

	boxComponent->SetCollisionChannel(ECollisionChannel::WorldStatic);
	boxComponent->SetCollisionResponce(ECollisionChannel::WorldDynamic, ECollisionResponse::Overlap);
	boxComponent->SetCollisionResponce(ECollisionChannel::WorldStatic, ECollisionResponse::Ignore);

	boxComponent->OnBeginOverlap.Add(std::bind(&Monster::OnCollision, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	SetTag("monster");
}

void Monster::Tick(double DeltaTime)
{
	GameObject::Tick(DeltaTime);
}

void Monster::Destroy()
{
	GameObject::Destroy();
	spriteComponent->Destroy();
}

void Monster::OnCollision(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime)
{
	std::string tag = otherObject->GetTag();
	if (tag == "doodle" && normal.y >= 0 && !static_pointer_cast<Doodle>(otherObject)->HasImmunity())
	{
		std::shared_ptr<DJGameMode> gameMode = static_pointer_cast<DJGameMode>(GetGameMode());
		gameMode->KillDoodle();
	}

}
