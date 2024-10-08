#include "MyFramework.h"
#include "Input/EventHandler.h"
#include "Input/TriggerEvent.h"
#include "Input/Events.h"
#include "Core/Base/AssetManager.h"
#include "Core/Base/GameInstance.h"
#include "Renderer/Renderer.h"
#include "World/World.h"


MyFramework::MyFramework(uint32_t w, uint32_t h, bool fs, const std::string& contentDirectory)
	: m_Width(w), m_Height(h), m_FullscreenMode(fs), m_ContentDirectory(contentDirectory)
{

}

void MyFramework::PreInit(int& width, int& height, bool& fullscreen)
{
	width = m_Width;
	height = m_Height;
	fullscreen = m_FullscreenMode;
	CreateAssetManager();
}

bool MyFramework::Init()
{
	m_AssetManager->Init();
	auto& assetMap = AssetManager::Get().GetMap();
	m_World = World::Create();
	m_EventHandler = EventHandler::Create();
	m_EventHandler->Init();

	Renderer::Init();

	m_KeyStates[FRKey::RIGHT] = false;
	m_KeyStates[FRKey::LEFT] = false;
	m_KeyStates[FRKey::DOWN] = false;
	m_KeyStates[FRKey::UP] = false;
	m_KeyStates[FRKey::COUNT] = false;

	m_MouseStates[FRMouseButton::LEFT] = false;
	m_MouseStates[FRMouseButton::MIDDLE] = false;
	m_MouseStates[FRMouseButton::RIGHT] = false;
	m_MouseStates[FRMouseButton::COUNT] = false;

	int32_t w, h;
	getScreenSize(w, h);
	m_World->Init(w, h);

	m_LastTime = (float)(getTickCount() / 1000.0f);
	return true;
}

void MyFramework::Close()
{
	m_World->Shutdown();
	delete m_AssetManager;
	delete m_GameInstance;
}

bool MyFramework::Tick()
{
	float Time = (float)(getTickCount() / 1000.0f);
	m_World->m_DeltaTime = Time - m_LastTime;
	m_LastTime = Time;
	if (m_World->m_DeltaTime > 0.05)
		m_World->m_DeltaTime = 0.05;

	// Generate Triggered Event
	for (auto it = m_KeyStates.begin(); it != m_KeyStates.end(); ++it)
		if (it->second)
			m_EventHandler->PushEvent(std::make_shared<KeyEvent>(it->first, EInputType::Key, ETriggerEvent::Triggered));

	for (auto it = m_MouseStates.begin(); it != m_MouseStates.end(); ++it)
		if (it->second)
			m_EventHandler->PushEvent(std::make_shared<MouseButtonEvent>(it->first, EInputType::MouseButton, ETriggerEvent::Triggered));


	m_EventHandler->HandleEvents();

	m_World->Update();

	return false;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative)
{
	Math::Vector2D coords({ (float)x,(float)y });
	m_EventHandler->PushEvent(std::make_shared<MouseMoveEvent>(coords, EInputType::MouseMove, ETriggerEvent::Triggered));
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased)
{
	if (isReleased)
	{
		m_EventHandler->PushEvent(std::make_shared<MouseButtonEvent>(button, EInputType::MouseButton, ETriggerEvent::Released));
		m_MouseStates[button] = false;
	}
	else
	{
		m_EventHandler->PushEvent(std::make_shared<MouseButtonEvent>(button, EInputType::MouseButton, ETriggerEvent::Pressed));
		m_MouseStates[button] = true;
	}
}

void MyFramework::onKeyPressed(FRKey k)
{
	m_EventHandler->PushEvent(std::make_shared<KeyEvent>(k, EInputType::Key, ETriggerEvent::Pressed));
	m_KeyStates[k] = true;
}

void MyFramework::onKeyReleased(FRKey k)
{
	m_EventHandler->PushEvent(std::make_shared<KeyEvent>(k, EInputType::Key, ETriggerEvent::Released));
	m_KeyStates[k] = false;
}

const char* MyFramework::GetTitle()
{
	return "DoodleJump";
}

void MyFramework::CreateAssetManager()
{
   m_AssetManager = new AssetManager(m_ContentDirectory);
}
