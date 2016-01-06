#ifndef ZJR_VECTOR_
#define ZJR_VECTOR_

#include <assert.h>
#include <math.h>

class Normal;
class Point;

class Vector
{
public:
	float				x;
	float				y;
	float				z;

	Vector();
	Vector(float x_, float y_, float z_);
	Vector(const Vector &v);
	Vector(const Point &p);
	Vector(const Normal &n);
	~Vector();

	Vector				operator+(const Vector &v) const;
	Vector				operator-(const Vector &v) const;
	Vector				operator-() const;
	Vector				operator*(float f) const;
	Vector				operator/(float f) const;
	float				operator[](int i) const;

	Vector&				operator+=(const Vector &v);
	Vector&				operator-=(const Vector &v);
	Vector&				operator*=(float f);
	Vector&				operator/=(float f);

	void				Normalize();
	Vector				Cross(const Vector &v) const;
	float				Dot(const Vector &v) const;
	float				AbsDot(const Vector &v) const;
	float				Length() const;
	float				LengthSquared() const;				
};

inline Vector Vector::operator+(const Vector &v) const
{
	return Vector(x + v.x, y + v.y, z + v.z);
}

inline Vector Vector::operator-(const Vector &v) const
{
	return Vector(x - v.x, y - v.y, z - v.z);
}

inline Vector Vector::operator-() const
{
	return Vector(-x, -y, -z);
}

inline Vector Vector::operator/(float f) const
{
	assert(f != 0);
	float inv = 1.0f / f;
	return Vector(x * inv, y * inv, z * inv);
}

inline void Vector::Normalize()
{
	auto len = this->Length();
	x /= len;
	y /= len;
	z /= len;
}

inline Vector Vector::Cross(const Vector &v) const
{
	return Vector(y * v.z - z * v.y,
					z * v.x - x * v.z,
					x * v.y - y * v.x);
}

inline float Vector::Dot(const Vector &v) const
{
	return x * v.x + y * v.y + z * v.z;
}

inline float Vector::AbsDot(const Vector &v) const
{
	return fabsf(Dot(v));
}

inline float Vector::Length() const
{
	return sqrtf(LengthSquared());
}

inline float Vector::LengthSquared() const
{
	return x * x + y * y + z * z;
}

inline Vector Vector::operator*(float f) const
{
	return Vector(x * f, y * f, z * f);
}

inline float Vector::operator[](int i) const
{
	assert(i >= 0 && i <= 2);
	return (&x)[i];
}

inline Vector& Vector::operator+=(const Vector &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

inline Vector& Vector::operator-=(const Vector &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

inline Vector& Vector::operator*=(float f)
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

inline Vector& Vector::operator/=(float f)
{
	assert(f != 0);
	float inv = 1.0f / f;
	x *= inv;
	y *= inv;
	z *= inv;
	return *this;
}

#endif