#pragma once
#include <memory>
#include "Object.h"

#include "Math/MyMath.h"
#include "Components/BasicComponents.h"

#include <memory>

class GameObject : public Object
{
	std::shared_ptr<SceneComponent> RootComponent;
};