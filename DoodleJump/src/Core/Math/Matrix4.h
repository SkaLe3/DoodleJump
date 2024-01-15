#pragma once
#include "Vector4D.h"
#include <string>

namespace Math
{

	struct Mat4
	{
	private:
		Vector4D value[4];

	public:
		Vector4D& operator[](size_t i);
		const Vector4D& operator[](size_t i) const;

		// Basic constructors
		Mat4();
		Mat4(const Mat4& m);
		Mat4(const double s);
		Mat4(
			double x0, double y0, double z0, double w0,
			double x1, double y1, double z1, double w1,
			double x2, double y2, double z2, double w2,
			double x3, double y3, double z3, double w3);
		Mat4(
			const Vector4D& v0,
			const Vector4D& v1,
			const Vector4D& v2,
			const Vector4D& v3);
		// Conversions
		// From Mat3 
		// From Mat2

		// Unary operators
		Mat4& operator=(const Mat4& m);
		Mat4& operator+=(const Mat4& m);
		Mat4& operator+=(double scalar);
		Mat4& operator-=(const Mat4& m);
		Mat4& operator-=(double scalar);
		Mat4& operator*=(const Mat4& m);
		Mat4& operator*=(double scalar);
		Mat4& operator/=(const Mat4& m);
		Mat4& operator/=(double scalar);
	};
	// Unary operators
	Mat4 operator+(const Mat4& m);
	Mat4 operator-(const Mat4& m);

	// Binary operators
	Mat4 operator+(const Mat4& m, double scalar);
	Mat4 operator+(double scalar, const Mat4& m);
	Mat4 operator+(const Mat4& m1, const Mat4& m2);

	Mat4 operator-(const Mat4& m, double scalar);
	Mat4 operator-(double scalar, const Mat4& m);
	Mat4 operator-(const Mat4& m1, const Mat4& m2);

	Mat4 operator*(const Mat4& m, double scalar);
	Mat4 operator*(double scalar, const Mat4& m);
	Vector4D operator*(const Mat4& m, const Vector4D& v);
	Vector4D operator*(const Vector4D& v, const Mat4& m);
	Mat4 operator*(const Mat4& m1, const Mat4& m2);

	Mat4 operator/(const Mat4& m, double scalar);
	Mat4 operator/(double scalar, const Mat4& m);
	Vector4D operator/(const Mat4& m, const Vector4D& v);
	Vector4D operator/(const Vector4D& v, const Mat4& m);
	Mat4 operator/(const Mat4& m1, const Mat4& m2);

	// Boolean operators
	bool operator==(const Mat4& m1, const Mat4& m2);
	bool operator!=(const Mat4& m1, const Mat4& m2);

	std::string MatToString(const Math::Mat4& m);
}