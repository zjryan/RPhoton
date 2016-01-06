#include "Normal.h"
#include "./Vector.h"


Normal::Normal()
	:	x(0.0f),
		y(1.0f),
		z(0.0f)
{
}

Normal::Normal(const Normal &n)
	:	x(n.x),
		y(n.y),
		z(n.z)
{
}

Normal::Normal(float x_, float y_, float z_)
	:	x(x_),
		y(y_),
		z(z_)
{
}

Normal::Normal(const Vector &v)
	:	x(v.x),
		y(v.y),
		z(v.z)
{
}

Normal::~Normal()
{
}

float Normal::Dot(const Vector &v) const
{
	return x * v.x + y * v.y + z * v.z;
}

float Normal::AbsDot(const Vector &v) const
{
	return fabsf(Dot(v));
}
