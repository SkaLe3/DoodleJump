#pragma once
#include "Framework.h"

#include <unordered_map>
#include <memory> 

class EventHandler;
class World;

class MyFramework : public Framework
{
public:
	MyFramework(uint32_t w, uint32_t h, bool fs);

public:
	//~ Begin Framework Interface
	virtual void PreInit(int& width, int& height, bool& fullscreen);
	virtual bool Init();
	virtual void Close();
	virtual bool Tick();

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative);
	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased);
	virtual void onKeyPressed(FRKey k);
	virtual void onKeyReleased(FRKey k);

	virtual const char* GetTitle() override;
	//~ End Framework Interface

private:
	float m_LastTime = 0;
	std::unordered_map<FRKey, bool> m_KeyStates;
	std::unordered_map<FRMouseButton, bool> m_MouseStates;

	std::shared_ptr<EventHandler> m_EventHandler;
	std::shared_ptr<World> m_World;

	uint32_t m_Width;
	uint32_t m_Height;
	bool m_FullscreenMode;
};