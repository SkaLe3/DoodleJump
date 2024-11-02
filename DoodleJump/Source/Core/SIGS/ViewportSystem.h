#pragma once
#include "WAnchors.h"
#include "WMargin.h"

#include <unordered_map>
#include <memory>

class Widget;

struct ViewportWidgetSlot
{
	WAnchors Anchors = WAnchors(0, 0, 1, 1);
	WMargin Offsets;
	Math::Vector2D Alignment = Math::Vector2D(0, 0);
	int32_t ZOrder = 0;
};


class ViewportSystem
{
public:
	static ViewportSystem& Get();

public:
	bool AddWidget(std::shared_ptr<Widget> widget, ViewportWidgetSlot slot);
	void RemoveWidget(std::shared_ptr<Widget> widget);
	ViewportWidgetSlot GetWidgetSlot(const std::shared_ptr<Widget> widget) const;
	// TODO: add delegates on added and on removed

private:
	// TODO: Move to GameViewport class or smth
	void AddViewportWidget(std::shared_ptr<Widget>, const int32_t ZOrder);

private:
	using ViewportWidgetList = std::unordered_map<std::shared_ptr<Widget>, ViewportWidgetSlot>;
	ViewportWidgetList m_ViewportWidgets;

private:
	static ViewportSystem* s_Instance;
};
