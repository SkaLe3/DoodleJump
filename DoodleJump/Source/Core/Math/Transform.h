#pragma once
#include "Vector.h"
#include "Matrix4.h"
#include "FuncMatrix.h"

namespace Math
{
	struct Transform
	{
		Math::Vector Translation = { 0.0, 0.0, 0.0 };
		Math::Vector Rotation = { 0.0, 0.0, 0.0 };	// Radians
		Math::Vector Scale = { 1.0, 1.0, 1.0 };

		Transform() = default;
		Transform(const Transform&) = default;
		Transform(const Math::Vector translation) : Translation(translation) {}

		Transform operator*(const Transform other) const
		{
			Transform newTransform;
			newTransform.Scale = Scale * other.Scale;
			newTransform.Rotation = Rotation + other.Rotation;

			Vector rotatedTranslation = Vector4D{ (other.Translation * Scale), 1 } *Rotate(Mat4(), Rotation.z);
			newTransform.Translation = rotatedTranslation + Translation;
			return newTransform;
		}

		Mat4 ToMat4()
		{
			return Translate(Mat4(), Translation)
				* Rotate(Mat4(), Rotation.z)
				* Math::Scale(Mat4(), Scale);
		}	
	};

}