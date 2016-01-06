#include "Sphere.h"
#include "../GraphicLib/Normal.h"
#include "../GraphicLib/Maths.h"

using namespace Math;

Sphere::Sphere()
	:	Geometry(),
		radius(1.0f),
		center(0.0f, 0.0f, 0.0f)
{
}

Sphere::Sphere(float rad, const Point &p)
	:	Geometry(),
		radius(rad),
		center(p)
{
}

Sphere::Sphere(const Sphere &s)
	:	Geometry(s),
		radius(s.radius),
		center(s.center)
{
}

Sphere::~Sphere()
{
}

void Sphere::SetRadius(float r)
{
	radius = r;
}

void Sphere::SetCenter(float x, float y, float z)
{
	center = Point(x, y, z);
}

bool Sphere::Intersect(const Ray &ray, float &t) const
{
	//compute quadratic sphere coefficients
	float A = ray.d.LengthSquared();
	float B = 2 * ray.d.Dot(ray.o - center);
	float C = Vector(ray.o - center).LengthSquared() - radius * radius;

	//solve quadratic equation for t values
	float t0, t1;
	if (!Quadratic(A, B, C, t0, t1))
	{
		return false;
	}
	t = t0;
	
	return true;
}

Normal Sphere::GetNormal(const Ray &ray, float &t) const
{
	Vector n(ray.o + ray.d * t - center);
	n.Normalize();
	return Normal(n);
}
