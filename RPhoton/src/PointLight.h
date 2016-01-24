#ifndef ZJR_POINTLIGHT_
#define ZJR_POINTLIGHT_

#include "Light.h"
#include "../GraphicLib/Vector3.h"
#include "../GraphicLib/Point.h"

class PointLight : public Light
{
public:
	Point				position;

	PointLight();
	PointLight(const Point &p);
	PointLight(const PointLight &pl);
	~PointLight();

	void				setPosition(float x, float y, float z);
	Color				intensity(const Point& hitPoint, const Normal &hitNormal) override;
	float				distance(const Point &p);
	Vector3				pointToLight(const Point &p);
	Vector3				lightToPoint(const Point &p);
};

#endif
