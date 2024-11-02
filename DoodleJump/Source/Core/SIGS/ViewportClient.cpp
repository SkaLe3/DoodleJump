#include "ViewportClient.h"



void ViewportClient::Tick(double deltaTime)
{

}

void ViewportClient::AddViewportWidgetContent(std::shared_ptr<Widget> content, const int32_t zOrder)
{
	if (m_ViewportOverlay)
	{
		//m_ViewportOverlay->AddSlot(zOrder)[content];
	}
}

void ViewportClient::RemoveViewportWidgetContent(std::shared_ptr<Widget> content)
{
	if (m_ViewportOverlay)
	{
		//m_ViewportOverlay->RemoveSlot(content);
	}
}

void ViewportClient::RemoveAll()
{

}
