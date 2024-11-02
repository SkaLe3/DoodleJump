#pragma once
#include "WMargin.h"
#include "WAnchors.h"
#include "Core/Math/Vector2D.h"

#include <memory>

struct AnchorData
{
public:
	WMargin Offsets;
	WAnchors Anchors;
	Math::Vector2D Alignment = Math::Vector2D::ZeroVector;
};


class PanelWidget;
class Widget;

class PanelSlot
{

public:
	void SetLayout(const AnchorData& inLayoutData);
	AnchorData GetLayout() const;

	void SetPosition(Math::Vector2D inPosition);
	Math::Vector2D GetPosition() const;

	void SetSize(Math::Vector2D inSize);
	Math::Vector2D GetSize() const;

	void SetOffsets(WMargin inOffset);
	WMargin GetOffsets() const;

	void SetAnchors(WAnchors inAnchors);
	WAnchors GetAnchors() const;

	void SetAlignment(Math::Vector2D inAlignment);
	Math::Vector2D GetAlignment() const;

	void SetZOrder(int32_t inZOrder);
	int32_t GetZOrder() const;


public:
	std::shared_ptr<PanelWidget> Parent;
	std::shared_ptr<Widget> Content;

public:
	AnchorData LayoutData;
	int32_t ZOrder;

};