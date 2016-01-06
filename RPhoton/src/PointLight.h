#ifndef ZJR_POINTLIGHT_
#define ZJR_POINTLIGHT_

#include "Light.h"
#include "../GraphicLib/Vector.h"
#include "../GraphicLib/Point.h"

class PointLight : public Light
{
public:
	Point				position;

	PointLight();
	PointLight(const Point &p);
	PointLight(const PointLight &pl);
	~PointLight();

	void				SetPosition(float x, float y, float z);
	Color				I(const Point& hitPoint, const Normal &hitNormal) override;
	float				Distance(const Point &p);
	Vector				PointToLight(const Point &p);
	Vector				LightToPoint(const Point &p);
};

#endif
