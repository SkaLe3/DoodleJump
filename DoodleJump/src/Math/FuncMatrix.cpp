#include "FuncMatrix.h"
#include "Matrix4.h"
#include "Vector.h"
#include <cmath>

namespace Math
{

	Mat4 Transpose(const Mat4& m)
	{
		Mat4 result;
		result[0][0] = m[0][0];
		result[0][1] = m[1][0];
		result[0][2] = m[2][0];
		result[0][3] = m[3][0];

		result[1][0] = m[0][1];
		result[1][1] = m[1][1];
		result[1][2] = m[2][1];
		result[1][3] = m[3][1];

		result[2][0] = m[0][2];
		result[2][1] = m[1][2];
		result[2][2] = m[2][2];
		result[2][3] = m[3][2];

		result[3][0] = m[0][3];
		result[3][1] = m[1][3];
		result[3][2] = m[2][3];
		result[3][3] = m[3][3];
		return result;
	}

	double Determinant(const Mat4& m)
	{
		double subCofactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		double subCofactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		double subCofactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		double subCofactor11 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		double subCofactor12 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		double subCofactor22 = m[2][0] * m[3][1] - m[3][0] * m[2][1];

		Vector4D cofactors(
			+(m[1][1] * subCofactor00 - m[1][2] * subCofactor01 + m[1][3] * subCofactor02),
			-(m[1][0] * subCofactor00 - m[1][2] * subCofactor11 + m[1][3] * subCofactor12),
			+(m[1][0] * subCofactor01 - m[1][1] * subCofactor11 + m[1][3] * subCofactor22),
			-(m[1][0] * subCofactor02 - m[1][1] * subCofactor12 + m[1][2] * subCofactor22));

		return m[0][0] * cofactors[0] + m[0][1] * cofactors[1] +
			m[0][2] * cofactors[2] + m[0][3] * cofactors[3];
	}

	Mat4 Inverse(const Mat4& m)
	{
		double det = Determinant(m);
		if (det == 0)
			return Mat4();

		double subCofactor000 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		double subCofactor001 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		double subCofactor002 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		double subCofactor011 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		double subCofactor012 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		double subCofactor022 = m[2][0] * m[3][1] - m[3][0] * m[2][1];

		double subCofactor200 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		double subCofactor201 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		double subCofactor202 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		double subCofactor211 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		double subCofactor212 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		double subCofactor222 = m[1][0] * m[3][1] - m[3][0] * m[1][1];

		double subCofactor300 = m[1][2] * m[2][3] - m[2][2] * m[1][3];
		double subCofactor301 = m[1][1] * m[2][3] - m[2][1] * m[1][3];
		double subCofactor302 = m[1][1] * m[2][2] - m[2][1] * m[1][2];
		double subCofactor311 = m[1][0] * m[2][3] - m[2][0] * m[1][3];
		double subCofactor312 = m[1][0] * m[2][2] - m[2][0] * m[1][2];
		double subCofactor322 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		Vector4D cofactors1(
			+(m[1][1] * subCofactor000 - m[1][2] * subCofactor001 + m[1][3] * subCofactor002),
			-(m[1][0] * subCofactor000 - m[1][2] * subCofactor011 + m[1][3] * subCofactor012),
			+(m[1][0] * subCofactor001 - m[1][1] * subCofactor011 + m[1][3] * subCofactor022),
			-(m[1][0] * subCofactor002 - m[1][1] * subCofactor012 + m[1][2] * subCofactor022));

		
		Vector4D cofactors2(
			-(m[0][1] * subCofactor000 - m[0][2] * subCofactor001 + m[0][3] * subCofactor002),
			+(m[0][0] * subCofactor000 - m[0][2] * subCofactor011 + m[0][3] * subCofactor012),
			-(m[0][0] * subCofactor001 - m[0][1] * subCofactor011 + m[0][3] * subCofactor022),
			+(m[0][0] * subCofactor002 - m[0][1] * subCofactor012 + m[0][2] * subCofactor022));
		

		Vector4D cofactors3(
			+(m[0][1] * subCofactor200 - m[0][2] * subCofactor201 + m[0][3] * subCofactor202),
			-(m[0][0] * subCofactor200 - m[0][2] * subCofactor211 + m[0][3] * subCofactor212),
			+(m[0][0] * subCofactor201 - m[0][1] * subCofactor211 + m[0][3] * subCofactor222),
			-(m[0][0] * subCofactor202 - m[0][1] * subCofactor212 + m[0][2] * subCofactor222));


		Vector4D cofactors4(
			-(m[0][1] * subCofactor300 - m[0][2] * subCofactor301 + m[0][3] * subCofactor302),
			+(m[0][0] * subCofactor300 - m[0][2] * subCofactor311 + m[0][3] * subCofactor312),
			-(m[0][0] * subCofactor301 - m[0][1] * subCofactor311 + m[0][3] * subCofactor322),
			+(m[0][0] * subCofactor302 - m[0][1] * subCofactor312 + m[0][2] * subCofactor322));

		Mat4 result(
			cofactors1.x, cofactors1.y, cofactors1.z, cofactors1.w,
			cofactors2.x, cofactors2.y, cofactors2.z, cofactors2.w,
			cofactors3.x, cofactors3.y, cofactors3.z, cofactors3.w,
			cofactors4.x, cofactors4.y, cofactors4.z, cofactors4.w);

		double oneOverDet = 1 / det;


		return oneOverDet * result;
	}

	Mat4 Translate(const Mat4& m, const Vector& v)
	{
		Mat4 result(m);
		result[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
		return result;
	}

	Mat4 Rotate(const Mat4& m, double angle, const Vector& v)
	{
		double c = cos(angle);
		double s = sin(angle);

		Mat4 result;
		result[0][0] = c;
		result[0][1] = s;
		result[1][0] = -s;
		result[1][1] = c;
		return result;
	}

	Mat4 Scale(const Mat4& m, Vector& v)
	{
		Mat4 result;
		result[0] = m[0] * v[0];
		result[1] = m[1] * v[1];
		result[2] = m[2] * v[2];
		result[3] = m[3];
		return result;
	}

	Math::Mat4 Orthographic(double left, double right, double bottom, double top)
	{
		Mat4 result;
		result[0][0] = 2.0 / (right - left);
		result[1][1] = 2.0 / (top - bottom);
		result[2][2] = -1.0;
		result[3][0] = -(right + left) / (right - left);
		result[3][1] = -(top + bottom) / (top - bottom);
		return result;

	}

}