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
	void SetCoordinates(Math::Vector2D coords);

	std::shared_ptr<NumberComponent> GetNumberComponent();

private:
	std::shared_ptr<NumberComponent> m_NumberComponent;
	Math::Vector2D m_Coordinates;
};