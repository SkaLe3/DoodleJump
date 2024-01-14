#pragma once
#include "Entities/GameObject.h"

class SpriteComponent;

class Doodle : public GameObject
{
	Doodle();

private:
	std::shared_ptr<SpriteComponent> spriteComponent;
};