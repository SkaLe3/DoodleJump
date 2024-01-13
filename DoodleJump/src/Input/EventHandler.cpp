#include "EventHandler.h"
#include "Framework.h"

#include <stdexcept>
#include <memory>

#include <iostream>

void EventHandler::Init()
{
	// Input Mapping
	keyActionMap[FRKey::RIGHT] = std::make_pair(1, EInputAction::Move);
	keyActionMap[FRKey::LEFT] = std::make_pair(-1, EInputAction::Move);
	mouseButtonActionMap[FRMouseButton::LEFT] = EInputAction::Shoot;
}

void EventHandler::BindAction(EInputAction action, ETriggerEvent triggerEvent, std::function<void(InputValue&)> func)
{
	bindings[action][triggerEvent] = func;
}

void EventHandler::PushEvent(std::shared_ptr<InputEvent> ie)
{
	queue.push(ie);
}

void EventHandler::HandleEvents()
{
	while (!queue.empty())
	{
		std::shared_ptr<InputEvent> e = queue.front();
		EInputAction action = EInputAction::None;
		InputValue value;
		
		if (e->GetEventType() == EInputType::Key)
		{
			try {
				std::pair<int32_t, EInputAction> values = keyActionMap.at(static_pointer_cast<KeyEvent>(e)->GetKey());
				action = values.second;
				value = Math::Vector1D(values.first);
			}
			catch (const std::out_of_range& e) {}
		}	

		if (e->GetEventType() == EInputType::MouseButton)
		{
			try {
				action = mouseButtonActionMap.at(static_pointer_cast<MouseButtonEvent>(e)->GetMouseButton());
			}
			catch (const std::out_of_range& e) {}
		}

		if(e->GetEventType() == EInputType::MouseMove)
		{
			action = EInputAction::Aim;
			value = static_pointer_cast<MouseMoveEvent>(e)->GetValue();
		}
		if (action == EInputAction::None)
		{
			queue.pop();
			return;
		}

		try {
			auto function = bindings.at(action).at(e->GetInputState());
			function(value);
		}
		catch (const std::out_of_range& e) {}

		queue.pop();
	}
}
