#pragma once
#include "SceneComponent.h"
#include "BoxCollider.h"

#include <unordered_map>
#include <functional>

enum class ECollisionChannel
{
	WorldStatic, WorldDynamic, Character
};
enum class ECollisionResponse
{
	Ignore, Overlap
};

class GameObject;

struct BeginOverlapDelegate
{
public:
	void Add(std::function<void(std::shared_ptr<GameObject>, Math::Vector2D, double)> callback);

	void operator()(std::shared_ptr<GameObject> otherObject, Math::Vector2D normal, double collisionTime);

private:
	std::vector<std::function<void(std::shared_ptr<GameObject>, Math::Vector2D, double)>> callbacks;	
};

class BoxComponent : public SceneComponent
{
public:
	BoxComponent();

	//~ Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;
	//~ End Object Interface
public:
	Math::Vector2D GetVelocity();
	Math::Vector2D GetHalfSize() const;
	ECollisionChannel GetCollisionChannel();
	ECollisionResponse GetCollisionResponce(ECollisionChannel channel);
	bool IsCollisionEnabled();
	void SetAcceleration(Math::Vector2D newAcceleration);
	BoxCollider GetCollider();

	void SetVelocity(Math::Vector2D newVelocity);
	void SetHalfSize(const Math::Vector2D& newSize);
	void SetCollisionChannel(ECollisionChannel channel);
	void SetCollisionResponce(ECollisionChannel channel, ECollisionResponse response);
	void SetCollisionEnabled(bool bEnabled);
	void SetGravity(Math::Vector2D newGravity);

public:
	BeginOverlapDelegate OnBeginOverlap;
	
private:
	Math::Vector2D m_BoxHalfSize;
	bool m_bCollisionEnabled;
	ECollisionChannel m_CollisionChannel = ECollisionChannel::WorldStatic;
	std::unordered_map<ECollisionChannel, ECollisionResponse> m_CollisionResponce;

	Math::Vector2D m_Velocity;
	Math::Vector2D m_Acceleration;
	Math::Vector2D m_Gravity;
};

