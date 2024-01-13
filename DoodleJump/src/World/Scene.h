#pragma once
#include "Entities/GameObject.h"
#include <vector>
class Scene
{
public:
	void Tick(float DeltaTime);

private:

	std::vector<Object> objects;
};