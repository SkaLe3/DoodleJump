#pragma once

#ifdef D_DEBUG
#define SPRITE_PATH const char* spritePath; 
#define GET_SPRITE_PATH() spritePath
#define SET_SPRITE_PATH(x) spritePath = x;
#else
#define SPRITE_PATH
#define GET_SPRITE_PATH() ""
#define SET_SPRITE_PATH(x)
#endif

class Sprite;

class MySprite
{
public:
	MySprite(const char* path);
	~MySprite();

	Sprite* Get();

private:
	Sprite* m_Sprite;
	SPRITE_PATH
};