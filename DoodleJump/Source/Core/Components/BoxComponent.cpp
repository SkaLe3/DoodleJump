#include "BoxComponent.h"
#include "World/World.h"
#include "Entities/GameObject.h"

BoxComponent::BoxComponent() : SceneComponent(), m_BoxHalfSize{ 0.5, 0.5 }, m_bCollisionEnabled(true)
{
	m_CollisionResponce[ECollisionChannel::Character] = ECollisionResponse::Overlap;
	m_CollisionResponce[ECollisionChannel::WorldDynamic] = ECollisionResponse::Overlap;
	m_CollisionResponce[ECollisionChannel::WorldStatic] = ECollisionResponse::Overlap;

	m_Velocity = Math::Vector2D::ZeroVector;
	m_Acceleration = Math::Vector2D::ZeroVector;
	m_Gravity = Math::Vector2D::ZeroVector;
}

void BoxComponent::Start()
{

}

void BoxComponent::Tick(double deltaTime)
{

}

void BoxComponent::Destroy()
{
	GetScene()->DestroyCollisionObject(GetSelf());
}

void BoxComponent::SetHalfSize(const Math::Vector2D& newSize)
{
	m_BoxHalfSize = newSize;
}

Math::Vector2D BoxComponent::GetHalfSize() const
{
	return m_BoxHalfSize;
}

void BoxComponent::SetCollisionChannel(ECollisionChannel channel)
{
	m_CollisionChannel = channel;
}

ECollisionChannel BoxComponent::GetCollisionChannel()
{
	return m_CollisionChannel;
}

void BoxComponent::SetCollisionResponce(ECollisionChannel channel, ECollisionResponse response)
{
	m_CollisionResponce[channel] = response;
}

ECollisionResponse BoxComponent::GetCollisionResponce(ECollisionChannel channel)
{
	return m_CollisionResponce[channel];
}

void BoxComponent::SetCollisionEnabled(bool bEnabled)
{
	m_bCollisionEnabled = bEnabled;
}

bool BoxComponent::IsCollisionEnabled()
{
	return m_bCollisionEnabled;
}

void BoxComponent::SetVelocity(Math::Vector2D newVelocity)
{
	m_Velocity = newVelocity;
}

Math::Vector2D BoxComponent::GetVelocity()
{
	Math::Vector2D accelerationCopy = m_Acceleration;
	Math::Vector2D velocityCopy = m_Velocity;
	accelerationCopy += m_Gravity;
	velocityCopy += accelerationCopy * 0.5 * GetWorld()->GetDeltaTime();
	return velocityCopy * GetWorld()->GetDeltaTime();
}

void BoxComponent::SetAcceleration(Math::Vector2D newAcceleration)
{
	m_Acceleration = newAcceleration;
}

void BoxComponent::SetGravity(Math::Vector2D newGravity)
{
	m_Gravity = newGravity;
}

BoxCollider BoxComponent::GetCollider()
{
	BoxCollider collider;
	collider.pos = GetWorldTransform().Translation;
	collider.size = GetWorldTransform().Scale * Math::Vector(m_BoxHalfSize, 0);
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
