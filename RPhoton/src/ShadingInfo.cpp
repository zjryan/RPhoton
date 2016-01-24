#include "ShadingInfo.h"
#include "Geometry.h"
#include "../GraphicLib/Ray.h"
#include "../GraphicLib/Maths.h"


ShadingInfo::ShadingInfo()
	:	isIntersected(false),
		t(INFINITY),
		hitGeo(nullptr),
		hitPoint(),
		hitNormal(),
		texCoord()	
{
}

ShadingInfo::~ShadingInfo()
{
}

void ShadingInfo::updateShadingInfo(const Ray &ray)
{
	hitPoint = Point(ray.o + ray.d * t);
	hitNormal = hitGeo->normal(ray, t);
	texCoord = hitGeo->texCoord(ray, t);
}
