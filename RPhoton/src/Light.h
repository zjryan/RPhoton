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

	void				setColor(const Color& c);
	void				setIntensity(float k);

	//return the hitPoint light intensity
	virtual Color		intensity(const Point& hitPoint, const Normal &hitNormal);
};

#endif
