#include "Triangle.h"
#include "../GraphicLib/Ray.h"


Triangle::Triangle()
	:	a(),
		b(),
		c()
{
}

Triangle::Triangle(const Vertex &a_, const Vertex &b_, const Vertex &c_)
	:	a(a_),
		b(b_),
		c(c_)
{
}

Triangle::Triangle(const Triangle &t)
	:	a(t.a),
		b(t.b),
		c(t.c)
{
}

Triangle::~Triangle()
{
}

Triangle& Triangle::operator=(const Triangle &rhs)
{
	if(this == &rhs)
	{
		return *this;
	}

	a = rhs.a;
	b = rhs.b;
	c = rhs.c;

	return *this;
}

float Triangle::area() const
{
	float E0 = (b.position - a.position).length();
	float E1 = (c.position - a.position).length();
	float E2 = (c.position - b.position).length();
	float p = (E0 + E1 + E2) / 2;

	return sqrtf(p * (p - E0) * (p - E1) * (p - E2));
}

bool Triangle::intersected(const Ray &ray, float &t) const
{
	float A = a.position.x - b.position.x;
	float B = a.position.y - b.position.y;
	float C = a.position.z - b.position.z;

	float D = a.position.x - c.position.x;
	float E = a.position.y - c.position.y;
	float F = a.position.z - c.position.z;

	float G = ray.d.x;
	float H = ray.d.y;
	float I = ray.d.z;

	float J = a.position.x - ray.o.x;
	float K = a.position.y - ray.o.y;
	float L = a.position.z - ray.o.z;

	float M = A * (E * I - H * F) + B * (G * F - D * I) + C * (D * H - E * G);
	float beta = (J * (E * I - H * F) + K * (G * F - D * I) + L * (D * H - E * G)) / M;
	float gama = (I * (A * K - J * B) + H * (J * C - A * L) + G * (B * L - K * C)) / M;
	float thit = -(F * (A * K - J * B) + E * (J * C - A * L) + D * (B * L - K * C)) / M;

	if(beta + gama < 1 && beta > 0 && gama > 0)
	{
		if(thit < t)
		{
			t = thit;
		}
		return true;
	}
	return false;
}

