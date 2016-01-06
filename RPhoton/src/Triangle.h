#ifndef ZJR_TRIANGLE_
#define ZJR_TRIANGLE_

#include "Geometry.h"
#include "../GraphicLib/Point.h"
#include "../GraphicLib/Normal.h"

class Triangle : public Geometry
{
public:
	Triangle(const Point &a, const Point &b, const Point &c);
	Triangle(const Point &a, const Point &b, const Point &c, const Normal &n);
	Triangle(const Triangle &t);
	~Triangle();

	float				Area() const;
	bool				Intersect(const Ray &ray, float &t) const override;
	Normal				GetNormal(const Ray &ray, float &t) const override;

private:
	Point				a;
	Point				b;
	Point				c;
	Normal				n;
};

#endif
