#pragma once
#include "Entities/GameObject.h"

class NumberComponent;

class NumberWidget : public GameObject
{
public:
	NumberWidget();
	~NumberWidget();

	virtual void Start() override;
	virtual void Tick(double deltaTime) override;
	virtual void Destroy() override;

	void Init(int32_t digits);
	void Update(int32_t number);

	void SetCoordinates(Math::Vector2D coords);

	std::shared_ptr<NumberComponent> GetNumberComponent();

private:

	std::shared_ptr<NumberComponent> numberComponent;
	Math::Vector2D coordinates;
};