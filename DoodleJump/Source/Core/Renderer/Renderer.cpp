#include "Renderer.h"
#include "Math/FuncMatrix.h"
#include "Renderer/MySprite.h"
#include "Framework.h"

RendererData Renderer::s_Data;

void Renderer::Init()
{
	s_Data.spriteCornersPositions[0] = { -0.5, -0.5, 0.0, 1.0 };
	s_Data.spriteCornersPositions[1] = {  0.5,  0.5, 0.0, 1.0 };
}

void Renderer::BeginScene(const Math::Mat4& cameraProjection, const Math::Mat4& cameraTransform)
{
	s_Data.viewProjection = cameraProjection * Math::Inverse(cameraTransform);
}

void Renderer::DrawSprite(const Math::Mat4& transform, std::shared_ptr<MySprite> sprite)
{
	Math::Mat4 MVP = s_Data.viewProjection * transform;
	Math::Vector4D position = MVP * Math::Vector4D(0, 0, 0, 1);

	Math::Vector4D vertices[2];
	vertices[0] = MVP * s_Data.spriteCornersPositions[0];
	vertices[1] = MVP * s_Data.spriteCornersPositions[1];

	// Find sprite size in screen coordinates
	double sizeX = vertices[1].x - vertices[0].x;
	double sizeY = vertices[0].y - vertices[1].y;

	// Offset sprite origin to its geometrical center
	int32_t offsetX = (int32_t)(sizeX / 2.0);
	int32_t offsetY = (int32_t)(sizeY / 2.0);

	setSpriteSize(sprite->Get(), (int32_t)sizeX, (int32_t)sizeY);
	drawSprite(sprite->Get(), (int32_t)position.x - offsetX, (int32_t)position.y - offsetY);
}
