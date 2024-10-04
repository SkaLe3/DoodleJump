#include "Matrix4.h"
#include "FuncMatrix.h"
#include <sstream>

namespace Math
{
	Mat4::Mat4() 
		: value{ Vector4D(1, 0, 0, 0), Vector4D(0, 1, 0, 0), Vector4D(0, 0, 1, 0), Vector4D(0, 0, 0, 1) } {}

	Mat4::Mat4(const Mat4& m) 
		: value{ Vector4D(m[0]), Vector4D(m[1]), Vector4D(m[2]), Vector4D(m[3]) } {}

	Mat4::Mat4(const double s)
		: value{Vector4D(s, 0, 0, 0), Vector4D(0, s, 0, 0), Vector4D(0, 0, s, 0), Vector4D(0, 0, 0, s)} {}

	Mat4::Mat4(
		double x0, double y0, double z0, double w0, 
		double x1, double y1, double z1, double w1, 
		double x2, double y2, double z2, double w2, 
		double x3, double y3, double z3, double w3)
		: value{	
			Vector4D(x0, y0, z0, w0),
			Vector4D(x1, y1, z1, w1),
			Vector4D(x2, y2, z2, w2),
			Vector4D(x3, y3, z3, w3)} { }

	Mat4::Mat4(const Vector4D& v0, const Vector4D& v1, const Vector4D& v2, const Vector4D& v3) 
		: value{v0, v1, v2, v3} {}

	Vector4D& Mat4::operator[](size_t i) { return value[i]; }

	const Math::Vector4D& Mat4::operator[](size_t i) const { return value[i]; }

	Mat4& Mat4::operator=(const Mat4& m)
	{
		value[0] = m[0];
		value[1] = m[1];
		value[2] = m[2];
		value[3] = m[3];
		return *this;
	}

	Mat4& Mat4::operator+=(const Mat4& m)
	{
		value[0] += m[0];
		value[1] += m[1];
		value[2] += m[2];
		value[3] += m[3];
		return *this;
	}

	Mat4& Mat4::operator+=(double scalar)
	{
		value[0] += scalar;
		value[1] += scalar;
		value[2] += scalar;
		value[3] += scalar;
		return *this;
	}

	Mat4& Mat4::operator-=(const Mat4& m)
	{
		value[0] -= m[0];
		value[1] -= m[1];
		value[2] -= m[2];
		value[3] -= m[3];
		return *this;
	}

	Mat4& Mat4::operator-=(double scalar)
	{
		value[0] -= scalar;
		value[1] -= scalar;
		value[2] -= scalar;
		value[3] -= scalar;
		return *this;
	}

	Mat4& Mat4::operator*=(const Mat4& m)
	{
		return (*this = *this * m);
	}

	Mat4& Mat4::operator*=(double scalar)
	{
		value[0] *= scalar;
		value[1] *= scalar;
		value[2] *= scalar;
		value[3] *= scalar;
		return *this;
	}

	Mat4& Mat4::operator/=(const Mat4& m)
	{
		return *this *= Inverse(m);
	}

	Mat4& Mat4::operator/=(double scalar)
	{
		value[0] /= scalar;
		value[1] /= scalar;
		value[2] /= scalar;
		value[3] /= scalar;
		return *this;
	}

	

	// Unary operators
	Mat4 operator+(const Mat4& m) { return m; }
	Mat4 operator-(const Mat4& m) { return Mat4(-m[0], -m[1], -m[2], -m[3]); }

	// Binary operators
	Mat4 operator+(const Mat4& m, double scalar) { return Mat4(m[0] + scalar, m[1] + scalar, m[2] + scalar, m[3] + scalar); }
	Mat4 operator+(double scalar, const Mat4& m) { return Mat4(m[0] + scalar, m[1] + scalar, m[2] + scalar, m[3] + scalar); }
	Mat4 operator+(const Mat4& m1, const Mat4& m2) { return Mat4(m1[0] + m2[0], m1[1] + m2[1], m1[2] + m2[2], m1[3] + m2[3]); }

	Mat4 operator-(const Mat4& m, double scalar) { return Mat4(m[0] - scalar, m[1] - scalar, m[2] - scalar, m[3] - scalar); }
	Mat4 operator-(double scalar, const Mat4& m) { return Mat4(scalar - m[0], scalar - m[1], scalar - m[2], scalar - m[3]); }
	Mat4 operator-(const Mat4& m1, const Mat4& m2) { return Mat4(m1[0] - m2[0], m1[1] - m2[1], m1[2] - m2[2], m1[3] - m2[3]); }

	Mat4 operator*(const Mat4& m, double scalar) { return Mat4(m[0] * scalar, m[1] * scalar, m[2] * scalar, m[3] * scalar); }
	Mat4 operator*(double scalar, const Mat4& m) { return Mat4(m[0] * scalar, m[1] * scalar, m[2] * scalar, m[3] * scalar); }
	Vector4D operator*(const Mat4& m, const Vector4D& v)
	{
		return Vector4D(
			m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3],
			m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3],
			m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3],
			m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3]);
	}
	Vector4D operator*(const Vector4D& v, const Mat4& m)
	{
		return Vector4D(
			m[0][0] * v[0] + m[0][1] * v[1] + m[0][2] * v[2] + m[0][3] * v[3],
			m[1][0] * v[0] + m[1][1] * v[1] + m[1][2] * v[2] + m[1][3] * v[3],
			m[2][0] * v[0] + m[2][1] * v[1] + m[2][2] * v[2] + m[2][3] * v[3],
			m[3][0] * v[0] + m[3][1] * v[1] + m[3][2] * v[2] + m[3][3] * v[3]);
	}
	Mat4 operator*(const Mat4& m1, const Mat4& m2)
	{
		Mat4 Result;
		Result[0] = m1[0] * m2[0][0] + m1[1] * m2[0][1] + m1[2] * m2[0][2] + m1[3] * m2[0][3];
		Result[1] = m1[0] * m2[1][0] + m1[1] * m2[1][1] + m1[2] * m2[1][2] + m1[3] * m2[1][3];
		Result[2] = m1[0] * m2[2][0] + m1[1] * m2[2][1] + m1[2] * m2[2][2] + m1[3] * m2[2][3];
		Result[3] = m1[0] * m2[3][0] + m1[1] * m2[3][1] + m1[2] * m2[3][2] + m1[3] * m2[3][3];
		return Result;
	}

	Mat4 operator/(const Mat4& m, double scalar) { return Mat4(m[0] / scalar, m[1] / scalar, m[2] / scalar, m[3] / scalar); }
	Mat4 operator/(double scalar, const Mat4& m) { return Mat4(scalar/ m[0], scalar / m[1], scalar / m[2], scalar / m[3]); }
	Vector4D operator/(const Mat4& m, const Vector4D& v) { return Inverse(m) * v; }
	Vector4D operator/(const Vector4D& v, const Mat4& m) { return v * Inverse(m); }
	Mat4 operator/(const Mat4& m1, const Mat4& m2)
	{
		Mat4 m1Copy;
		return m1Copy /= m2;
	}

	// Boolean operators
	bool operator==(const Mat4& m1, const Mat4& m2)
	{
		return (m1[0] == m2[0]) && (m1[1] == m2[1]) && (m1[2] == m2[2]) && (m1[3] == m2[3]);
	}
	bool operator!=(const Mat4& m1, const Mat4& m2)
	{
		return (m1[0] != m2[0]) || (m1[1] != m2[1]) || (m1[2] != m2[2]) || (m1[3] != m2[3]);
	}

	std::string MatToString(const Mat4& m)
	{
		std::stringstream sout;
		sout << m[0][0] << ", " << m[1][0] << ", " << m[2][0] << ", " << m[3][0] << "\n";
		sout << m[0][1] << ", " << m[1][1] << ", " << m[2][1] << ", " << m[3][1] << "\n";
		sout << m[0][2] << ", " << m[1][2] << ", " << m[2][2] << ", " << m[3][2] << "\n";
		sout << m[0][3] << ", " << m[1][3] << ", " << m[2][3] << ", " << m[3][3] << "\n";
		return sout.str();
	}
}