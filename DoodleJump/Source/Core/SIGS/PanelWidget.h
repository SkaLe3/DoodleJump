#pragma once
#include "Widget.h"

#include <vector>

class PanelWidget : public Widget
{

public:
	size_t GetChildrenCount() const;
	int32_t GetChildIndex(const std::shared_ptr<Widget> content) const;
	std::shared_ptr<Widget> GetChildAt(int32_t index) const;
	std::shared_ptr<PanelSlot> AddChild(std::shared_ptr<Widget> content);
	bool RemoveChild(std::shared_ptr<Widget> content);
	bool RemoveChildAt(size_t index);

protected:
	/* Slots with child widgets */
	std::vector<std::shared_ptr<PanelSlot>> m_Slots;
};