#pragma once

namespace Math
{
	struct Mat4;
	struct Vector;

	Mat4 Transpose(const Mat4& m);
	double Determinant(const Mat4& m);
	Mat4 Inverse(const Mat4& m);

	Mat4 Translate(const Mat4& m, const Vector& v);
	Mat4 Rotate(const Mat4& m, double angle);
	Mat4 Scale(const Mat4& m, Vector& v);

	Mat4 Orthographic(double left, double right, double bottom, double top);

	// May be add LookAt
}