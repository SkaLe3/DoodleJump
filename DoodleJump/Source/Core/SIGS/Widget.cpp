#include "Widget.h"
#include "ViewportSystem.h"
#include "PanelSlot.h"
#include "PanelWidget.h"


std::shared_ptr<PanelWidget> Widget::GetParent() const
{
	if (Slot)
	{
		return Slot->Parent;
	}
	return nullptr;
}

void Widget::RemoveFromParent()
{
	if (m_bManagedByViewportSystem)
	{

		ViewportSystem& vs = ViewportSystem::Get();
		vs.RemoveWidget(GetSelf().lock());

	}
	else if (std::shared_ptr<PanelWidget> parent = GetParent())
	{
		parent->RemoveChild(GetSelf().lock());
	}

}
