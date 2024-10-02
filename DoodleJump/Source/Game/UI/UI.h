#pragma once
#include "Core/Math/MyMath.h"
#include "Core/World/World.h"
#include "GameObjects/UI/NumberWidget.h"

#include <string>

class UI
{
public:
	static std::shared_ptr<NumberWidget> CreateNumberWidget(Math::Vector2D coords, uint32_t digits);
	static void CreateWidget(const std::string& assetName, Math::Vector2D coords, Math::Vector2D scale, double zLocation);

	static void UpdateWidget(std::shared_ptr<NumberWidget> widget, int32_t newValue);
};

