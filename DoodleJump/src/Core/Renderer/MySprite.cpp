#include "MySprite.h"
#include "Framework.h"

#include <iostream>
MySprite::MySprite(const char* path)
{
	sprite = createSprite(path);
}

MySprite::~MySprite()
{
	destroySprite(sprite);
}

Sprite* MySprite::Get()
{
	return sprite;
}
