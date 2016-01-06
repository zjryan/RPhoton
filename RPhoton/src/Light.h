#ifndef ZJR_LIGHT_
#define ZJR_LIGHT_

#include "../GraphicLib/Color.h"

class Point;
class Normal;

class  Light
{
public:
	float				k;
	Color				color;

	Light();
	Light(const Light &l);
	virtual ~Light();

	void				SetColor(const Color& c);
	void				SetIntensity(float k);

	//return the hitPoint light intensity
	virtual Color		I(const Point& hitPoint, const Normal &hitNormal);
};

#endif
