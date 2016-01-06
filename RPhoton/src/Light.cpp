#include "Light.h"

Light::Light()
	:	k(0.2),
		color()
{
}

Light::~Light()
{
}

void Light::SetIntensity(float i)
{
	k = i;
}

void Light::SetColor(const Color& c)
{
	color = c;
}

Light::Light(const Light& l)
	:	k(l.k),
		color(l.color)
{
}

Color Light::I(const Point& hitPoint, const Normal &hitNormal)
{
	return color * k;
}

