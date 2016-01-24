#ifndef ZJR_SHADINGINFO_
#define ZJR_SHADINGINFO_

#include "../GraphicLib/Normal.h"
#include "../GraphicLib/Point.h"
#include "Texture.h"

class Geometry;
class Ray;

class ShadingInfo
{
public:
	Geometry*			hitGeo;
	Point				hitPoint;
	Normal				hitNormal;
	Vector2				texCoord;
	bool				isIntersected;
	float				t;

public:
	ShadingInfo();
	~ShadingInfo();

	void updateShadingInfo(const Ray &ray);
};

#endif
