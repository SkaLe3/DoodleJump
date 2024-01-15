#pragma once
#include "SceneComponent.h"
#include "Math/Vector2D.h"

// Move to another file
enum class ECollisionChannel
{
	WorldStatic, WorldDynamic, Character
};
enum class ECollisionResponse
{
	Ignore, Overlap
};

class BoxComponent : public SceneComponent
{
public:
	BoxComponent() : SceneComponent(), boxSize{1, 1} {}

	virtual void Start() override { SceneComponent::Start(); }
	virtual void Tick(double DeltaTime) override { SceneComponent::Tick(DeltaTime); }

	void SetSize(const Math::Vector2D& newSize) { boxSize = newSize; }
	Math::Vector2D GetSize() const { return boxSize; }
	
private:

	Math::Vector2D boxSize;
	
};