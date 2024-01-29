#include "BoxComponent.h"
#include "World/World.h"
#include "Entities/GameObject.h"

BoxComponent::BoxComponent() : SceneComponent(), boxHalfSize{ 0.5, 0.5 }, bCollisionEnabled(true)
{
	collisionResponce[ECollisionChannel::Character] = ECollisionResponse::Overlap;
	collisionResponce[ECollisionChannel::WorldDynamic] = ECollisionResponse::Overlap;
	collisionResponce[ECollisionChannel::WorldStatic] = ECollisionResponse::Overlap;

	velocity = Math::Vector2D::ZeroVector;
	acceleration = Math::Vector2D::ZeroVector;
	gravity = Math::Vector2D::ZeroVector;
}

void BoxComponent::Start()
{

}

void BoxComponent::Tick(double deltaTime)
{

}

void BoxComponent::Destroy()
{
	GetScene()->DestroyCollisionObject(GetScene()->GetComponent(this));
}

void BoxComponent::SetHalfSize(const Math::Vector2D& newSize)
{
	boxHalfSize = newSize;
}

Math::Vector2D BoxComponent::GetHalfSize() const
{
	return boxHalfSize;
}

void BoxComponent::SetCollisionChannel(ECollisionChannel channel)
{
	collisionChannel = channel;
}

ECollisionChannel BoxComponent::GetCollisionChannel()
{
	return collisionChannel;
}

void BoxComponent::SetCollisionResponce(ECollisionChannel channel, ECollisionResponse response)
{
	collisionResponce[channel] = response;
}

ECollisionResponse BoxComponent::GetCollisionResponce(ECollisionChannel channel)
{
	return collisionResponce[channel];
}

void BoxComponent::SetCollisionEnabled(bool bEnabled)
{
	bCollisionEnabled = bEnabled;
}

bool BoxComponent::IsCollisionEnabled()
{
	return bCollisionEnabled;
}

void BoxComponent::SetVelocity(Math::Vector2D newVelocity)
{
	velocity = newVelocity;
}

Math::Vector2D BoxComponent::GetVelocity()
{
	Math::Vector2D accelerationCopy = acceleration;
	Math::Vector2D velocityCopy = velocity;
	accelerationCopy += gravity;
	velocityCopy += accelerationCopy * 0.5 * GetWorld()->GetDeltaTime();
	return velocityCopy * GetWorld()->GetDeltaTime();
}

void BoxComponent::SetAcceleration(Math::Vector2D newAcceleration)
{
	acceleration = newAcceleration;
}

void BoxComponent::SetGravity(Math::Vector2D newGravity)
{
	gravity = newGravity;
}

BoxCollider BoxComponent::GetCollider()
{
	BoxCollider collider;
	collider.pos = GetTransform().Translation;
	collider.size = GetTransform().Scale * Math::Vector(boxHalfSize, 0);
	collider.vel = GetVelocity();
	return collider;
}

void BeginOverlapDelegate::Add(std::function<void(std::shared_ptr<GameObject>, Math::Vector2D, double)> callback)
{
	callbacks.push_back(callback);
}

void BeginOverlapDelegate::operator()(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime)
{
	for (auto& func : callbacks)
		func(otherObject, normal, collisionTime);
}
