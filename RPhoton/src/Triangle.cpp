#include "Triangle.h"
#include "../GraphicLib/Ray.h"

#include <iostream>
using namespace std;

Triangle::Triangle(const Point &a_, const Point &b_, const Point &c_)
	:	Geometry(),
		a(a_),
		b(b_),
		c(c_)
{
	Vector e0 = b - a;
	Vector e1 = c - a;
	Vector nor = e0.Cross(e1);
	nor.Normalize();
	n = Normal(nor);
}

Triangle::Triangle(const Point &a_, const Point &b_, const Point &c_, const Normal &n_)
	:	Geometry(),
		a(a_),
		b(b_),
		c(c_),
		n(n_)
{
}

Triangle::Triangle(const Triangle &t)
	:	Geometry(t),
		a(t.a),
		b(t.b),
		c(t.c),
		n(t.n)
{
}

Triangle::~Triangle()
{
}

float Triangle::Area() const 
{
	float E0 = (b - a).Length();
	float E1 = (c - a).Length();
	float E2 = (c - b).Length();
	float p = (E0 + E1 + E2) / 2;

	return sqrtf(p * (p - E0) * (p - E1) * (p - E2));
}

bool Triangle::Intersect(const Ray &ray, float &t) const
{
	float A = a.x - b.x;
	float B = a.y - b.y;
	float C = a.z - b.z;

	float D = a.x - c.x;
	float E = a.y - c.y;
	float F = a.z - c.z;

	float G = ray.d.x;
	float H = ray.d.y;
	float I = ray.d.z;

	float J = a.x - ray.o.x;
	float K = a.y - ray.o.y;
	float L = a.z - ray.o.z;

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

Normal Triangle::GetNormal(const Ray &ray, float &t) const
{
	return n;
}

