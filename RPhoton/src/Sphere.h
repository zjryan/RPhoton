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

	void				setRadius(float r);
	void				setCenter(float x, float y, float z);

	bool				intersected(const Ray &ray, float &t) const override;
	Normal				normal(const Ray &ray, float &t) const override;
	Vector2				texCoord(const Ray &ray, float &t) const override;

private:
	float				radius;
	Point				center;
};

#endif