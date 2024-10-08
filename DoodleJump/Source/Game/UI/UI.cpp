#include "UI.h"
#include "GameObjects/UI/SpriteWidget.h"
#include "Core/Base/AssetManager.h"
#include "Core/Components/CameraComponent.h"




std::shared_ptr<NumberWidget> UI::CreateNumberWidget(Math::Vector2D coords, uint32_t digits)
{
	std::shared_ptr<NumberWidget> widget = GetScene()->SpawnGameObject<NumberWidget>();
	widget->SetLocation({ coords, 0 });
	widget->Init(digits);
	widget->Start();
	widget->GetBoxComponent()->SetupAttachment(GetScene()->GetRenderCamera());
	return widget;
}

void UI::CreateWidget(const std::string& assetName, Math::Vector2D coords, Math::Vector2D scale, double zLocation)
{
	std::shared_ptr<SpriteWidget> sprite = GetScene()->SpawnGameObject<SpriteWidget>();
	sprite->SetLocation({coords, 0});
	sprite->GetBoxComponent()->SetupAttachment(GetScene()->GetRenderCamera());
	std::shared_ptr<SpriteComponent> sc = sprite->GetSprite();
	sc->SetSprite(AssetManager::Get().GetAsset<MySprite>(assetName));
	sc->GetTransform().Scale = { scale, 1 };
	sc->GetTransform().Translation.z = zLocation;
}

void UI::UpdateWidget(std::shared_ptr<NumberWidget> widget, int32_t newValue)
{

	widget->Update(newValue);
}
