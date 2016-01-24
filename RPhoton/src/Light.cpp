#include "Light.h"

Light::Light()
	:	k(0.6),
		color()
{
}

Light::~Light()
{
}

void Light::setIntensity(float i)
{
	k = i;
}

void Light::setColor(const Color& c)
{
	color = c;
}

Light::Light(const Light& l)
	:	k(l.k),
		color(l.color)
{
}

Color Light::intensity(const Point& hitPoint, const Normal &hitNormal)
{
	return color * k;
}

