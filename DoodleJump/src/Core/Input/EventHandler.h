#pragma once
#include "Input/Events.h"
#include "Input/TriggerEvent.h"
#include "Input/InputAction.h"
#include "Input/InputValue.h"
#include "Math/Vector2D.h"

#include <unordered_map>
#include <queue>
#include <functional>
#include <memory>



class EventHandler
{
public:
	EventHandler() = default;

	void Init();

	void BindAction(EInputAction, ETriggerEvent, std::function<void(InputValue&)> func);
	void ClearBindings();
	void PushEvent(std::shared_ptr<InputEvent> ie);
	void HandleEvents();

	Math::Vector2D GetMousePosition() const;
	
	static std::shared_ptr<EventHandler> Create() 
	{ 
		sInstance = std::make_shared<EventHandler>(); 
		return sInstance;
	}
	static std::shared_ptr<EventHandler> Get() { return sInstance; }

private:
	std::queue<std::shared_ptr<InputEvent>> queue;
	std::unordered_map<EInputAction, std::unordered_map<ETriggerEvent, std::function<void(InputValue&)>>> bindings;
	std::unordered_map<FRKey, std::pair<float, EInputAction>> keyActionMap;
	std::unordered_map<FRMouseButton, EInputAction> mouseButtonActionMap;

	Math::Vector2D lastMousePosition;

	static std::shared_ptr<EventHandler> sInstance;

};