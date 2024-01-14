#pragma once

namespace Math
{
	struct Mat4;

	Mat4 Transpose(const Mat4& m);
	double Determinant(const Mat4& m);
	Mat4 Inverse(const Mat4& m);
}