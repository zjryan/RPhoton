#ifndef ZJR_TRIANGLE_
#define ZJR_TRIANGLE_

#include "Geometry.h"
#include "../GraphicLib/Vertex.h"

class Triangle : public Geometry
{
public:
	Triangle();
	Triangle(const Vertex &a, const Vertex &b, const Vertex &c);
	Triangle(const Triangle &t);
	~Triangle();

	Triangle& operator=(const Triangle &rhs);

	float				area() const;
	bool				intersected(const Ray &ray, float &t) const override;
	Normal				normal(const Ray &ray, float &t) const override;
	Vector2				texCoord(const Ray &ray, float &t) const override;

private:
	Vertex				a;
	Vertex				b;
	Vertex				c;
};

#endif
