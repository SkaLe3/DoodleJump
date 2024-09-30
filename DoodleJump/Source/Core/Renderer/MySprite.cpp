#include "MySprite.h"
#include "Framework.h"
#include "Core/Base/Log.h"

MySprite::MySprite(const char* path)
{
	m_Sprite = createSprite(path);
	SET_SPRITE_PATH(path)
	LOG("MySprite c-tor: " + GET_SPRITE_PATH())
}

MySprite::~MySprite()
{
	destroySprite(m_Sprite);
	LOG("\033[33mMySprite d-tor: " + GET_SPRITE_PATH() + "\033[0m")
}

Sprite* MySprite::Get()
{
	return m_Sprite;
}
