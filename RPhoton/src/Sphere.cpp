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

void Sphere::setRadius(float r)
{
	radius = r;
}

void Sphere::setCenter(float x, float y, float z)
{
	center = Point(x, y, z);
}

bool Sphere::intersected(const Ray &ray, float &t) const
{
	//compute quadratic sphere coefficients
	float A = ray.d.lengthSquared();
	float B = 2 * ray.d.dot(ray.o - center);
	float C = Vector3(ray.o - center).lengthSquared() - radius * radius;

	//solve quadratic equation for t values
	float t0, t1;
	if (!quadratic(A, B, C, t0, t1))
	{
		return false;
	}
	t = t0;
	
	return true;
}

Normal Sphere::normal(const Ray &ray, float &t) const
{
	Vector3 n(ray.o + ray.d * t - center);
	n.normalize();
	return Normal(n);
}

Vector2 Sphere::texCoord(const Ray &ray, float &t) const
{
	Point p(ray.o + ray.d * t);
	float theta = acos((p.z - center.z) / radius);
	float phy = atan2f(p.y - center.y, p.x - center.x);

	return Vector2(phy / TWO_PI, (PI - theta) / PI);
}
