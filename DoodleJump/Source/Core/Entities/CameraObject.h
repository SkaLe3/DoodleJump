#pragma once
#include "Core/Entities/GameObject.h"
#include "Core/Components/CameraComponent.h"

class CameraObject : public	GameObject
{
public:
	CameraObject();
	~CameraObject();

	//~ Begin Object Interface
	virtual void Start() override;
	virtual void Destroy() override;
	//~ End Object Interface

	std::shared_ptr<CameraComponent> GetCameraComponent() const { return m_CameraComponent.lock(); }

private:
	std::weak_ptr<CameraComponent> m_CameraComponent;
};