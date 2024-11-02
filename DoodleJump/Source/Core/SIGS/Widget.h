#pragma once
#include <vector>
#include <string>
#include <memory>

#include "Core/Math/MyMath.h"

class PanelWidget;
class PanelSlot;
class ViewportSystem;


/* Base class for all widgets in SIG */
class Widget : public std::enable_shared_from_this<Widget>
{
	friend ViewportSystem;
public:
	//~ Begin Widget behavior
	Widget(const std::string& inName) : m_Name(inName) {}
	virtual ~Widget() = default;

	std::string GetName() { return m_Name; }
	inline std::weak_ptr<Widget> GetSelf() { return weak_from_this(); }

	// Somehow implement this
	void SetHover(bool inHovered) { m_bHovered = inHovered; }
	bool IsHovered() const {}

	std::shared_ptr<PanelWidget> GetParent() const;
	virtual void RemoveFromParent();
	//~ End Widget behavior

public:
	//~ Begin object behavior
	virtual void Tick(double deltaTime);
	virtual void onMouseButtonDown() {} // TODO: later make bindings
	// TODO: add tag

	//~ End object behavior
public:
	std::shared_ptr<PanelSlot> Slot;

protected:
	std::string m_Name;
	bool m_bManagedByViewportSystem;
	bool m_bHovered = false;
};