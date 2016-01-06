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

void PointLight::SetPosition(float x, float y, float z)
{
	position = Point(x, y, z);
}

Color PointLight::I(const Point& hitPoint, const Normal &hitNormal)
{
	Vector l = PointToLight(hitPoint);
	return Light::I(hitPoint, hitNormal) * l.Dot(hitNormal);
}

float PointLight::Distance(const Point& p)
{
	Vector dir = position - p;
	return dir.Length();
}

Vector PointLight::LightToPoint(const Point& p)
{
	Vector dir = p - position;
	dir.Normalize();
	return dir;
}

Vector PointLight::PointToLight(const Point& p)
{
	Vector dir = position - p;
	dir.Normalize();
	return dir;
}

