#pragma once
#include "Widget.h"
#include "Core/World/World.h"

#include <vector>
#include <memory>

class WidgetLayout : public Widget
{
public:
	WidgetLayout(const std::string& inName) : Widget(inName) {}

	void AddToViewport(int32_t zOrder = 0);

};


template <typename TWidgetL>
std::shared_ptr<TWidgetL> CreateWidgetLayout(const std::string& widgetName)
{
	return std::make_shared<TWidgetL>(widgetName);
}