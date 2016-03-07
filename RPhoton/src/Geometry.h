#ifndef ZJR_CEOMETRY_
#define ZJR_CEOMETRY_

#include "Material.h"
#include "../GraphicLib/Matrix4x4.h"

class Ray;
class Normal;

class Geometry
{
public:
	Material*			material;
	Matrix4x4			world;

	Geometry();
	Geometry(Material *material_);
	Geometry(const Geometry &geo);
	virtual ~Geometry() = 0;

	Geometry& operator=(const Geometry &rhs);

	virtual Vector2		texCoord(const Ray &ray, float &t) const = 0;
	virtual bool		intersected(const Ray &ray, float &t) const = 0;
	virtual Normal		normal(const Ray &ray, float &t) const = 0;
};

#endif

