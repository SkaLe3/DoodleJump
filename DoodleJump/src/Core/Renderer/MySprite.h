#pragma once

class Sprite;

class MySprite
{
public:
	MySprite(const char* path);
	~MySprite();

	Sprite* Get();

private:
	Sprite* sprite;
};