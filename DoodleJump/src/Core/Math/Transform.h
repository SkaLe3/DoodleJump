#pragma once
#include "Vector.h"
#include "Matrix4.h"
#include "FuncMatrix.h"

namespace Math
{
	struct Transform
	{
		Math::Vector Translation = { 0.0, 0.0, 0.0 };
		Math::Vector Rotation = { 0.0, 0.0, 0.0 };
		Math::Vector Scale = { 1.0, 1.0, 1.0 };

		Transform() = default;
		Transform(const Transform&) = default;
		Transform(const Math::Vector translation) : Translation(translation) {}

		Mat4 ToMat4()
		{
			return Translate(Mat4(), Translation)
				* Rotate(Mat4(), Rotation.z)
				* Math::Scale(Mat4(), Scale);
		}
		
	};

}