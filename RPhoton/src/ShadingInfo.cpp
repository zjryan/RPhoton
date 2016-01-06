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

void ShadingInfo::UpdateShadingInfo(const Ray &ray)
{
	hitPoint = Point(ray.o + ray.d * t);
	hitNormal = hitGeo->GetNormal(ray, t);
	texCoord = hitGeo->GetTexCoord(ray, t);
}
