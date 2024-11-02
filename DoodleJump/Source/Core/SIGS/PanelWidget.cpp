#include "PanelWidget.h"
#include "PanelSlot.h"
#include <algorithm>


size_t PanelWidget::GetChildrenCount() const
{
	return m_Slots.size();
}

int32_t PanelWidget::GetChildIndex(const std::shared_ptr<Widget> content) const
{
	if (content)
	{
	   const int32_t childCount = GetChildrenCount();
	   for (int32_t childIndex = 0; childIndex < childCount; childIndex++)
	   {
		   if (GetChildAt(childIndex) == content)
		   {
			   return childIndex;
		   }
	   }
	}
	return -1;
}

std::shared_ptr<Widget> PanelWidget::GetChildAt(int32_t index) const
{
	if (index < m_Slots.size() && index >= 0)
	{
		if (std::shared_ptr<PanelSlot> childSlot = m_Slots[index])
		{
			return childSlot->Content;	
		}
	}
	return nullptr;
}

std::shared_ptr<PanelSlot> PanelWidget::AddChild(std::shared_ptr<Widget> content)
{
	if (content == nullptr)
		return nullptr;
	content->RemoveFromParent();
	std::shared_ptr<PanelSlot> newSlot = std::make_shared<PanelSlot>();
	newSlot->Content = content;
	newSlot->Parent = std::static_pointer_cast<PanelWidget>(GetSelf().lock());
	content->Slot = newSlot;
	m_Slots.push_back(newSlot);
	return newSlot;
}

bool PanelWidget::RemoveChild(std::shared_ptr<Widget> content)
{
   int32_t childIndex = GetChildIndex(content);
   if (childIndex != -1)
   {
	   return RemoveChildAt(childIndex);
   }
   return false;
}

bool PanelWidget::RemoveChildAt(size_t index)
{
	if (index < 0 || index >= m_Slots.size())
		return false;

	std::shared_ptr<PanelSlot> panelSlot = m_Slots[index];
	m_Slots.erase(m_Slots.begin() + index);

	if (panelSlot)
	{
		if (panelSlot->Content)
		{
			panelSlot->Content->Slot = nullptr;
		}
		panelSlot->Parent = nullptr;
		panelSlot->Content = nullptr;
	}
	else
	{
		return false;
	}
	return true;
}
