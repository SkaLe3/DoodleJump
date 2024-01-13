

#include "Framework.h"
// Так само як в движку викликати OnEvent в колбеках но в OnEvent викликать прибінджені функції, як в анріалі

#include <iostream>
/* Test Framework realization */
class MyFramework : public Framework {

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = 320;
		height = 200;
		fullscreen = false;
	}

	virtual bool Init() {

		return true;
	}

	virtual void Close() {

	}

	virtual bool Tick() {
		float Time = (float) (getTickCount() / 1000.0f);
		float DeltaTime = Time - LastTime;
		LastTime = Time;



		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {

	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {

	}

	virtual void onKeyPressed(FRKey k) {
	}

	virtual void onKeyReleased(FRKey k) {
	}
	
	virtual const char* GetTitle() override
	{
		return "DoodleJump";
	}

	float LastTime;
};

int main(int argc, char *argv[])
{
	return run(new MyFramework);
}
