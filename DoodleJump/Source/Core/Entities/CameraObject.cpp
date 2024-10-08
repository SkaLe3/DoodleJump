#include "CameraObject.h"


CameraObject::CameraObject() : GameObject()
{
	m_CameraComponent = CreateComponent<CameraComponent>();
	auto camera = GetCameraComponent();
	camera->SetupAttachment(GetBoxComponent());
	GetScene()->UseCamera(m_CameraComponent);

	auto box = GetBoxComponent();
	box->SetCollisionEnabled(false);
	OBJECT_LOG_DESTRUCTOR()
}

CameraObject::~CameraObject()
{
	OBJECT_LOG_DESTRUCTOR()
}

void CameraObject::Start()
{
   GameObject::Start();
   GetCameraComponent()->SetOwner(GetSelf());
}

void CameraObject::Destroy()
{
   GameObject::Destroy();
   GetCameraComponent()->Destroy();
}
