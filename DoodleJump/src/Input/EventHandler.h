#pragma once
#include "Input/Events.h"
#include "Input/TriggerEvent.h"
#include "Input/InputAction.h"
#include "Input/InputValue.h"

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
	void PushEvent(std::shared_ptr<InputEvent> ie);
	void HandleEvents();
	

private:
	std::queue<std::shared_ptr<InputEvent>> queue;
	std::unordered_map<EInputAction, std::unordered_map<ETriggerEvent, std::function<void(InputValue&)>>> bindings;
	std::unordered_map<FRKey, std::pair<int32_t, EInputAction>> keyActionMap;
	std::unordered_map<FRMouseButton, EInputAction> mouseButtonActionMap;

};