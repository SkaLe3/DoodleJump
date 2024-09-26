#include "EventHandler.h"
#include "Framework.h"

#include <stdexcept>
#include <memory>

#include <iostream>

std::shared_ptr<EventHandler> EventHandler::s_Instance = nullptr;

void EventHandler::Init()
{
	// Input Mapping
	m_KeyActionMap[FRKey::RIGHT] = std::make_pair(1.f, EInputAction::Move);
	m_KeyActionMap[FRKey::LEFT] = std::make_pair(-1.f, EInputAction::Move);
	m_MouseButtonActionMap[FRMouseButton::LEFT] = EInputAction::Shoot;
}

void EventHandler::BindAction(EInputAction action, ETriggerEvent triggerEvent, std::function<void(InputValue&)> func)
{
	m_Bindings[action][triggerEvent] = func;
}

void EventHandler::ClearBindings()
{
	m_Bindings.clear();
}

void EventHandler::PushEvent(std::shared_ptr<InputEvent> ie)
{
	m_Queue.push(ie);
}

void EventHandler::HandleEvents()
{
	while (!m_Queue.empty())
	{
		std::shared_ptr<InputEvent> e = m_Queue.front();
		EInputAction action = EInputAction::None;
		InputValue value;
		
		if (e->GetEventType() == EInputType::Key)
		{
			try {
				std::pair<float, EInputAction> values = m_KeyActionMap.at(static_pointer_cast<KeyEvent>(e)->GetKey());
				action = values.second;
				value = values.first;
			}
			catch (...) {}
		}	

		if (e->GetEventType() == EInputType::MouseButton)
		{
			try {
				action = m_MouseButtonActionMap.at(static_pointer_cast<MouseButtonEvent>(e)->GetMouseButton());
			}
			catch (...) {}
		}

		if(e->GetEventType() == EInputType::MouseMove)
		{
			action = EInputAction::Aim;
			value = static_pointer_cast<MouseMoveEvent>(e)->GetValue();
			m_LastMousePosition = value.Get<Math::Vector2D>();
		}
		if (action == EInputAction::None)
		{
			m_Queue.pop();
			return;
		}

		try {
			auto function = m_Bindings.at(action).at(e->GetInputState());
			function(value);
		}
		catch (...) {}

		m_Queue.pop();
	}
}

Math::Vector2D EventHandler::GetMousePosition() const
{
	return m_LastMousePosition;
}
