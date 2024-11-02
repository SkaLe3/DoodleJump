#include "PanelSlot.h"



void PanelSlot::SetLayout(const AnchorData& inLayoutData)
{
	LayoutData = inLayoutData;
}

AnchorData PanelSlot::GetLayout() const
{
	return LayoutData;
}

void PanelSlot::SetPosition(Math::Vector2D inPosition)
{
	LayoutData.Offsets.Left = inPosition.x;
	LayoutData.Offsets.Top = inPosition.y;
}

Math::Vector2D PanelSlot::GetPosition() const
{
	return Math::Vector2D(LayoutData.Offsets.Left, LayoutData.Offsets.Top);
}

void PanelSlot::SetSize(Math::Vector2D inSize)
{
	LayoutData.Offsets.Right = inSize.x;
	LayoutData.Offsets.Bottom = inSize.y;
}

Math::Vector2D PanelSlot::GetSize() const
{
	return Math::Vector2D(LayoutData.Offsets.Right, LayoutData.Offsets.Bottom);
}

void PanelSlot::SetOffsets(WMargin inOffset)
{
	LayoutData.Offsets = inOffset;
}

WMargin PanelSlot::GetOffsets() const
{
	return LayoutData.Offsets;
}

void PanelSlot::SetAnchors(WAnchors inAnchors)
{
	LayoutData.Anchors = inAnchors;
}

WAnchors PanelSlot::GetAnchors() const
{
	return LayoutData.Anchors;
}

void PanelSlot::SetAlignment(Math::Vector2D inAlignment)
{
	LayoutData.Alignment = inAlignment;
}

Math::Vector2D PanelSlot::GetAlignment() const
{
	return LayoutData.Alignment;
}

void PanelSlot::SetZOrder(int32_t inZOrder)
{
	ZOrder = inZOrder;
}

int32_t PanelSlot::GetZOrder() const
{
	return ZOrder;
}
