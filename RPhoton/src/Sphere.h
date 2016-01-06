#ifndef ZJR_SPHERE_
#define ZJR_SPHERE_

#include "Geometry.h"
#include "../GraphicLib/Ray.h"

class Sphere : public Geometry
{
public:
	Sphere();
	Sphere(float rad, const Point &p);
	Sphere(const Sphere &s);
	~Sphere();

	void				SetRadius(float r);
	void				SetCenter(float x, float y, float z);

	bool				Intersect(const Ray &ray, float &t) const override;
	Normal				GetNormal(const Ray &ray, float &t) const override;

private:
	float				radius;
	Point				center;
};

#endif