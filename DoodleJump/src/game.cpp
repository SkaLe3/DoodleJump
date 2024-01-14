

#include "Framework.h"

#include "Input/TriggerEvent.h"
#include "Input/Events.h"
#include "Input/EventHandler.h"
#include "World/World.h"

#include <unordered_map>
#include <memory> // shared_ptr

// TESTING 
#include "Math/MyMath.h"
#include <iostream>
// END TESTING

/* Test Framework realization */
class MyFramework : public Framework {

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = 900;
		height = 600;
		fullscreen = false;
	}

	virtual bool Init() {
		world = World::Create();
		world->Init();
		eventHandler = EventHandler::Create();
		eventHandler->Init();

		KeyStates[FRKey::RIGHT] = false;
		KeyStates[FRKey::LEFT]  = false;
		KeyStates[FRKey::DOWN]  = false;
		KeyStates[FRKey::UP]	= false;
		KeyStates[FRKey::COUNT] = false;

		MouseStates[FRMouseButton::LEFT] = false;
		MouseStates[FRMouseButton::MIDDLE] = false;
		MouseStates[FRMouseButton::RIGHT] = false;
		MouseStates[FRMouseButton::COUNT] = false;

		

// 		std::cout << nt[0][0] << " " << nt[1][0] << " " << nt[2][0] << " " << nt[3][0] << "\n";
// 		std::cout << nt[0][1] << " " << nt[1][1] << " " << nt[2][1] << " " << nt[3][1] << "\n";
// 		std::cout << nt[0][2] << " " << nt[1][2] << " " << nt[2][2] << " " << nt[3][2] << "\n";
// 		std::cout << nt[0][3] << " " << nt[1][3] << " " << nt[2][3] << " " << nt[3][3] << "\n";

		return true;
	}

	virtual void Close() {

	}

	virtual bool Tick() {
		float Time = (float) (getTickCount() / 1000.0f);
		world->DeltaTime = Time - LastTime;
		LastTime = Time;

		// Generate Triggered Event
		for (auto it = KeyStates.begin(); it != KeyStates.end(); ++it) 
			if (it->second)
				eventHandler->PushEvent(std::make_shared<KeyEvent>(it->first, EInputType::Key, ETriggerEvent::Triggered));

		for (auto it = MouseStates.begin(); it != MouseStates.end(); ++it)
			if (it->second)
				eventHandler->PushEvent(std::make_shared<MouseButtonEvent>(it->first, EInputType::MouseButton, ETriggerEvent::Triggered));


		eventHandler->HandleEvents();

		world->Update();
		Math::Mat4 testmat(
			1, 2, 3, 1,
			4, 5, 6, 2,
			2, 8, 2, 3,
			4, 5, 6, 7
		);
		Math::Mat4 nt;
		for (int i = 0; i < 1000; i++)
			nt = Math::Inverse(testmat);

		std::cout << 1.0 / world->GetDeltaTime()<< std::endl;

		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {
		Math::Vector2D coords({ (float) x,(float) y });
		eventHandler->PushEvent(std::make_shared<MouseMoveEvent>(coords, EInputType::MouseMove, ETriggerEvent::Triggered));
	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {
		if (isReleased)
		{
			eventHandler->PushEvent(std::make_shared<MouseButtonEvent>(button, EInputType::MouseButton, ETriggerEvent::Released));
			MouseStates[button] = false;
		}
		else
		{	
			eventHandler->PushEvent(std::make_shared<MouseButtonEvent>(button, EInputType::MouseButton, ETriggerEvent::Pressed));
			MouseStates[button] = true;
		}
	}

	virtual void onKeyPressed(FRKey k) {	
		eventHandler->PushEvent(std::make_shared<KeyEvent>(k, EInputType::Key, ETriggerEvent::Pressed));
		KeyStates[k] = true;
	}

	virtual void onKeyReleased(FRKey k) {
		eventHandler->PushEvent(std::make_shared<KeyEvent>(k, EInputType::Key, ETriggerEvent::Released));
		KeyStates[k] = false;
	}
	
	virtual const char* GetTitle() override
	{
		return "DoodleJump";
	}

	float LastTime;
	std::unordered_map<FRKey, bool> KeyStates;
	std::unordered_map<FRMouseButton, bool> MouseStates;

	std::shared_ptr<EventHandler> eventHandler;
	std::shared_ptr<World> world;
};

int main(int argc, char *argv[])
{
	return run(new MyFramework);
}
