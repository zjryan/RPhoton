#include "PointLight.h"

PointLight::PointLight()
	:	Light(),
		position()
{
}

PointLight::PointLight(const Point& p)
	:	Light(),
		position(p)
{
}

PointLight::PointLight(const PointLight& pl)
	:	Light(pl),
		position(pl.position)
{
}

PointLight::~PointLight()
{
}

void PointLight::setPosition(float x, float y, float z)
{
	position = Point(x, y, z);
}

Color PointLight::intensity(const Point& hitPoint, const Normal &hitNormal)
{
	Vector3 l = pointToLight(hitPoint);
	return Light::intensity(hitPoint, hitNormal) * l.dot(hitNormal);
}

float PointLight::distance(const Point& p)
{
	Vector3 dir = position - p;
	return dir.length();
}

Vector3 PointLight::lightToPoint(const Point& p)
{
	Vector3 dir = p - position;
	dir.normalize();
	return dir;
}

Vector3 PointLight::pointToLight(const Point& p)
{
	Vector3 dir = position - p;
	dir.normalize();
	return dir;
}

