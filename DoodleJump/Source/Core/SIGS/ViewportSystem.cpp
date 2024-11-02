#include "ViewportSystem.h"
#include "Widget.h"
#include "Core/World/World.h"
#include "Core/Base/Log.h"



ViewportSystem* ViewportSystem::s_Instance = nullptr;
ViewportSystem& ViewportSystem::Get()
{
   return *s_Instance;
}

bool ViewportSystem::AddWidget(std::shared_ptr<Widget> widget, ViewportWidgetSlot slot)
{
	if (!widget)
	{
		LOG("Tried to add invalid widget");
		return false;
	}

	if (widget->GetParent())
	{
		LOG("Widget " + widget->GetName() + " already has a parent. Can't be added to viewport");
		return false;
	}

	ViewportWidgetSlot& slotInfo = m_ViewportWidgets[widget];
	widget->m_bManagedByViewportSystem = true;
	slotInfo = slot;

	std::shared_ptr<ViewportClient> vc = GetWorld()->GetViewportClient();
	vc->AddViewportWidgetContent(widget, slot.ZOrder);

	// TODO: broadcast
	return true;
}

void ViewportSystem::RemoveWidget(std::shared_ptr<Widget> widget)
{
	if (widget)
	{
		m_ViewportWidgets.erase(widget);
		// broadcast event
	}
}


ViewportWidgetSlot ViewportSystem::GetWidgetSlot(const std::shared_ptr<Widget> widget) const
{
	if (widget && widget->m_bManagedByViewportSystem)
	{
		auto slot = m_ViewportWidgets.find(widget);
		if (slot != m_ViewportWidgets.end())
		{
			return slot->second;
		}
	}
	return ViewportWidgetSlot();
}

void ViewportSystem::AddViewportWidget(std::shared_ptr<Widget>, const int32_t ZOrder)
{

}
