#ifndef ZJR_CEOMETRY_
#define ZJR_CEOMETRY_

#include "Material.h"

class Ray;
class Normal;

class Geometry
{
public:
	Material*			material;

	Geometry();
	Geometry(Material *material_);
	Geometry(const Geometry &geo);
	virtual ~Geometry() = 0;

	virtual Vector2		GetTexCoord(const Ray &ray, float &t) const = 0;
	virtual bool		Intersect(const Ray &ray, float &t) const = 0;
	virtual Normal		GetNormal(const Ray &ray, float &t) const = 0;
};

#endif

