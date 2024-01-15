

#include "Framework.h"

#include "Input/TriggerEvent.h"
#include "Input/Events.h"
#include "Input/EventHandler.h"
#include "World/World.h"
#include "Renderer/Renderer.h"
#include <unordered_map>
#include <memory> 


// TESTING 
#include "Math/MyMath.h"
#include <iostream>
// END TESTING

/* Test Framework realization */
class MyFramework : public Framework {

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
		width = 400;
		height = 800;
		fullscreen = false;
	}

	virtual bool Init() {
		world = World::Create();
		eventHandler = EventHandler::Create();
		eventHandler->Init();
		
		Renderer::Init();

		KeyStates[FRKey::RIGHT] = false;
		KeyStates[FRKey::LEFT]  = false;
		KeyStates[FRKey::DOWN]  = false;
		KeyStates[FRKey::UP]	= false;
		KeyStates[FRKey::COUNT] = false;

		MouseStates[FRMouseButton::LEFT] = false;
		MouseStates[FRMouseButton::MIDDLE] = false;
		MouseStates[FRMouseButton::RIGHT] = false;
		MouseStates[FRMouseButton::COUNT] = false;

		world->Init();
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
