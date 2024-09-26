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
	static std::shared_ptr<EventHandler> Create()
	{
		s_Instance = std::make_shared<EventHandler>();
		return s_Instance;
	}
	static std::shared_ptr<EventHandler> Get() { return s_Instance; }

public:
	EventHandler() = default;

	void Init();

	void BindAction(EInputAction, ETriggerEvent, std::function<void(InputValue&)> func);
	void ClearBindings();
	void PushEvent(std::shared_ptr<InputEvent> ie);
	void HandleEvents();

	Math::Vector2D GetMousePosition() const;
	
private:
	static std::shared_ptr<EventHandler> s_Instance;

	std::queue<std::shared_ptr<InputEvent>> m_Queue;
	std::unordered_map<EInputAction, std::unordered_map<ETriggerEvent, std::function<void(InputValue&)>>> m_Bindings;
	std::unordered_map<FRKey, std::pair<float, EInputAction>> m_KeyActionMap;
	std::unordered_map<FRMouseButton, EInputAction> m_MouseButtonActionMap;

	Math::Vector2D m_LastMousePosition;
};