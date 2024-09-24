#include "MySprite.h"
#include "Framework.h"
#include "Core/Base/Log.h"

MySprite::MySprite(const char* path)
{
	sprite = createSprite(path);
	SET_SPRITE_PATH(path)
	LOG("MySprite c-tor: " + std::string(GET_SPRITE_PATH()))
}

MySprite::~MySprite()
{
	destroySprite(sprite);
	LOG("MySprite d-tor: " + std::string(GET_SPRITE_PATH()))
}

Sprite* MySprite::Get()
{
	return sprite;
}
