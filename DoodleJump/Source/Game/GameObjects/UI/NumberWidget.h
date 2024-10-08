#pragma once
#include "Core/Entities/GameObject.h"

class NumberComponent;

class NumberWidget : public GameObject
{
public:
	NumberWidget();
	~NumberWidget();

	//~ Begin Object Interface
	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;
	//~ End Object Interface

	void Init(int32_t digits);
	void Update(int32_t number);

	std::shared_ptr<NumberComponent> GetNumberComponent();

private:
	std::weak_ptr<NumberComponent> m_NumberComponent;
};