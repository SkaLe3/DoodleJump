#include "WidgetLayout.h"
#include "ViewportSystem.h"


void WidgetLayout::AddToViewport(int32_t zOrder /*= 0*/)
{
	ViewportSystem& vs = ViewportSystem::Get();
	ViewportWidgetSlot slot;
	if (m_bManagedByViewportSystem)
	{
		slot = vs.GetWidgetSlot(GetSelf().lock());
	}
	slot.ZOrder = zOrder;
	vs.AddWidget(GetSelf().lock(), slot);
}
