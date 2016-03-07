#ifndef ZJR_MATRIX_
#define ZJR_MATRIX_

#include "Maths.h"
#include "Vector3.h"

struct Matrix4x4
{
	float				m[4][4];

	Matrix4x4();
	Matrix4x4(float mat[4][4]);
	Matrix4x4(float t00, float t01, float t02, float t03,
			  float t10, float t11, float t12, float t13,
			  float t20, float t21, float t22, float t23,
			  float t30, float t31, float t32, float t33);

	Matrix4x4			transpose() const;
	Matrix4x4			inverse() const;
	Matrix4x4			mul(const Matrix4x4 &mat);
	float				determinant() const;

	bool				operator==(const Matrix4x4 &m) const;
	bool				operator!=(const Matrix4x4 &m) const;

	friend Vector3		operator*(const Vector3 &v, const Matrix4x4 &m);
};

inline Matrix4x4::Matrix4x4()
{
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if(r != c)
			{
				m[r][c] = 0.0f;
			}
			else
			{
				m[r][c] = 1.0f;
			}
		}
	}
}

inline Matrix4x4::Matrix4x4(float mat[4][4])
{
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			m[r][c] = mat[r][c];
		}
	}
}

inline Matrix4x4::Matrix4x4(float t00, float t01, float t02, float t03, 
							float t10, float t11, float t12, float t13, 
							float t20, float t21, float t22, float t23, 
							float t30, float t31, float t32, float t33)
{
	m[0][0] = t00; m[0][1] = t01; m[0][2] = t02; m[0][3] = t03;
	m[1][0] = t10; m[1][1] = t11; m[1][2] = t12; m[1][3] = t13;
	m[2][0] = t20; m[2][1] = t21; m[2][2] = t22; m[2][3] = t23;
	m[3][0] = t30; m[3][1] = t31; m[3][2] = t32; m[3][3] = t33;
}

inline Matrix4x4 Matrix4x4::transpose() const
{
	return Matrix4x4(m[0][0], m[1][0], m[2][0], m[3][0],
					 m[0][1], m[1][1], m[2][1], m[3][1],
					 m[0][2], m[1][2], m[2][2], m[3][2],
					 m[0][3], m[1][3], m[2][3], m[3][3]);
}


inline Matrix4x4 Matrix4x4::inverse() const
{
	/*
	| a b c 0 |
	| d e f 0 |
	| g h i 0 |
	| 0 0 0 1 |
	*/

	Matrix4x4 r;
	double fDetInv = 1.0 / determinant();

	r.m[0][0] =  fDetInv * (m[1][1] * m[2][2] - m[1][2] * m[2][1]);
	r.m[0][1] = -fDetInv * (m[0][1] * m[2][2] - m[0][2] * m[2][1]);
	r.m[0][2] =  fDetInv * (m[0][1] * m[1][2] - m[0][2] * m[1][1]);
	r.m[0][3] = 0;

	r.m[1][0] = -fDetInv * (m[1][0] * m[2][2] - m[1][2] * m[2][0]);
	r.m[1][1] =  fDetInv * (m[0][0] * m[2][2] - m[0][2] * m[2][0]);
	r.m[1][2] = -fDetInv * (m[0][0] * m[1][2] - m[0][2] * m[1][0]);
	r.m[1][3] = 0;
		  
	r.m[2][0] =  fDetInv * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
	r.m[2][1] = -fDetInv * (m[0][0] * m[2][1] - m[0][1] * m[2][0]);
	r.m[2][2] =  fDetInv * (m[0][0] * m[1][1] - m[0][1] * m[1][0]);
	r.m[2][3] = 0;
		  
	r.m[3][0] = -(m[3][0] * r.m[0][0] + m[3][1] * r.m[1][0] + m[3][2] * r.m[2][0]);
	r.m[3][1] = -(m[3][0] * r.m[0][1] + m[3][1] * r.m[1][1] + m[3][2] * r.m[2][1]);
	r.m[3][2] = -(m[3][0] * r.m[0][2] + m[3][1] * r.m[1][2] + m[3][2] * r.m[2][2]);
	r.m[3][3] = 1;
		
	return r;
}

inline Matrix4x4 Matrix4x4::mul(const Matrix4x4 &mat)
{
	Matrix4x4 mr;
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			mr.m[r][c] = m[r][0] * mat.m[0][c] +
							m[r][1] * mat.m[1][c] +
							m[r][2] * mat.m[2][c] +
							m[r][3] * mat.m[3][c];
		}
	}

	return mr;
}

inline float Matrix4x4::determinant() const
{
	return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
			m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
			m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
}

inline bool Matrix4x4::operator==(const Matrix4x4 &mat) const
{
	for (int r = 0; r < 4; ++r)
	{
		for (int c = 0; c < 4; ++c)
		{
			if(m[r][c] != mat.m[r][c])
			{
				return false;
			}
		}
	}

	return true;
}

inline bool Matrix4x4::operator!=(const Matrix4x4 &m) const
{
	return !operator==(m);
}

__forceinline Vector3 operator*(const Vector3 &v, const Matrix4x4 &m)
{
	return Vector3();
}

namespace Transform
{
	__forceinline Matrix4x4 MatrixTranslate(float x, float y, float z)
	{
		return Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
						 0.0f, 1.0f, 0.0f, 0.0f,
						 0.0f, 0.0f, 1.0f, 0.0f,
						    x,	  y,    z, 1.0f);
	}

	__forceinline Matrix4x4 MatrixScale(float x, float y, float z)
	{
		return Matrix4x4(   x, 0.0f, 0.0f, 0.0f,
						 0.0f,    y, 0.0f, 0.0f,
						 0.0f, 0.0f,    z, 0.0f,
						 0.0f, 0.0f, 0.0f, 1.0f);
	}

	__forceinline Matrix4x4 MatrixRotateX(float angle)
	{
		float radian = Math::radians(angle);
		float s = sinf(radian);
		float c = cosf(radian);
		return Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
						 0.0f,    c,    s, 0.0f,
						 0.0f,   -s,    c, 0.0f,
						 0.0f, 0.0f, 0.0f, 1.0f);
	}

	__forceinline Matrix4x4 MatrixRotateY(float angle)
	{
		float radian = Math::radians(angle);
		float s = sinf(radian);
		float c = cosf(radian);
		return Matrix4x4(   c, 0.0f,   -s, 0.0f,
						 0.0f, 1.0f, 0.0f, 0.0f,
						    s, 0.0f,    c, 0.0f,
						 0.0f, 0.0f, 0.0f, 1.0f);
	}

	__forceinline Matrix4x4 MatrixRotateZ(float angle)
	{
		float radian = Math::radians(angle);
		float s = sinf(radian);
		float c = cosf(radian);
		return Matrix4x4(   c,    s, 0.0f, 0.0f,
						   -s,    c, 0.0f, 0.0f,
						 0.0f, 0.0f, 1.0f, 0.0f,
						 0.0f, 0.0f, 0.0f, 1.0f);
	}
}
#endif
