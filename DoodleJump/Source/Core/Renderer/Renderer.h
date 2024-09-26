#pragma once
#include "Math/Matrix4.h"

#include <memory>

class MySprite;

struct RendererData
{
	Math::Vector4D spriteCornersPositions[2];
	Math::Mat4 viewProjection;
};

class Renderer
{
public:
	static void Init();
	static void BeginScene(const Math::Mat4& cameraProjection, const Math::Mat4& cameraTransform);
	static void DrawSprite(const Math::Mat4& transform, std::shared_ptr<MySprite> sprite);

private:
	static RendererData s_Data;
};	