#include "Vector.h"
#include "./Point.h"
#include "./Normal.h"

Vector::Vector()
	:	x(0.0f),
		y(0.0f),
		z(0.0f)
{
}

Vector::Vector(float x_, float y_, float z_)
	:	x(x_),
		y(y_),
		z(z_)
{
}

Vector::Vector(const Vector &v)
	:	x(v.x),
		y(v.y),
		z(v.z)
{
}

Vector::Vector(const Point& p)
	:	x(p.x),
		y(p.y),
		z(p.z)
{
}


Vector::Vector(const Normal& n)
	:	x(n.x),
		y(n.y),
		z(n.z)
{
}

Vector::~Vector()
{
}



