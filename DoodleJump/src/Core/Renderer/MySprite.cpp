#include "MySprite.h"
#include "Framework.h"

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
