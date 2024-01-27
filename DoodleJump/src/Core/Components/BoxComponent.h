#pragma once
#include "SceneComponent.h"
#include "Math/Vector2D.h"
#include "Math/Vector.h"
#include "BoxCollider.h"
#include <unordered_map>
#include <functional>
#include <vector>

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

	virtual void Start() override;
	virtual void Tick(double DeltaTime) override;
	virtual void Destroy() override;

public:
	// Collision
	void SetHalfSize(const Math::Vector2D& newSize);
	Math::Vector2D GetHalfSize() const;

	void SetCollisionChannel(ECollisionChannel channel);
	ECollisionChannel GetCollisionChannel();

	void SetCollisionResponce(ECollisionChannel channel, ECollisionResponse response);
	ECollisionResponse GetCollisionResponce(ECollisionChannel channel);

	void SetCollisionEnabled(bool bEnabled);
	bool IsCollisionEnabled();


	// Movement
	void SetVelocity(Math::Vector2D newVelocity);
	Math::Vector2D GetVelocity();

	void SetAcceleration(Math::Vector2D newAcceleration);
	void SetGravity(Math::Vector2D newGravity);

	BoxCollider GetCollider();

public:
	BeginOverlapDelegate OnBeginOverlap;
	
private:

	Math::Vector2D boxHalfSize;
	bool bCollisionEnabled;
	ECollisionChannel collisionChannel = ECollisionChannel::WorldStatic;
	std::unordered_map<ECollisionChannel, ECollisionResponse> collisionResponce;

	Math::Vector2D velocity;
	Math::Vector2D acceleration;
	Math::Vector2D gravity;
	
};

