#pragma once
#include <memory>

class Overlay;
class Widget;

class ViewportClient
{
public:
	void Tick(double deltaTime);
	void AddViewportWidgetContent(std::shared_ptr<Widget> content, const int32_t zOrder);
	void RemoveViewportWidgetContent(std::shared_ptr<Widget> content);
	void RemoveAll();


private:
	std::unique_ptr<Overlay> m_ViewportOverlay;
};