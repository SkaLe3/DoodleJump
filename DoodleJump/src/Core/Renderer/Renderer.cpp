#include "Renderer.h"
#include "Math/FuncMatrix.h"
#include "Renderer/MySprite.h"
#include "Framework.h"

RendererData Renderer::sData;

void Renderer::Init()
{
	sData.spriteCornersPositions[0] = { -0.5, -0.5, 0.0, 1.0 };
	sData.spriteCornersPositions[1] = {  0.5,  0.5, 0.0, 1.0 };
}

void Renderer::BeginScene(const Math::Mat4& cameraProjection, const Math::Mat4& cameraTransform)
{
	sData.viewProjection = cameraProjection * Math::Inverse(cameraTransform);
}

void Renderer::DrawSprite(const Math::Mat4& transform, std::shared_ptr<MySprite> sprite)
{
	Math::Mat4 MVP = sData.viewProjection * transform;
	Math::Vector4D position = MVP * Math::Vector4D(0, 0, 0, 1);

	Math::Vector4D vertices[2];
	vertices[0] = MVP * sData.spriteCornersPositions[0];
	vertices[1] = MVP * sData.spriteCornersPositions[1];

	// Find sprite size in screen coordinates
	double sizeX = vertices[1].x - vertices[0].x;
	double sizeY = vertices[0].y - vertices[1].y;

	// Offset sprite origin to its geometrical center
	int32_t offsetX = sizeX / 2.0;
	int32_t offsetY = sizeY / 2.0;

	setSpriteSize(sprite->Get(), sizeX, sizeY);
	drawSprite(sprite->Get(), position.x - offsetX, position.y - offsetY);
}
