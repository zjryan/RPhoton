#ifndef ZJR_TRIANGLE_
#define ZJR_TRIANGLE_

#include "../GraphicLib/Vertex.h"

class Ray;

class Triangle
{
public:
	Triangle();
	Triangle(const Vertex &a, const Vertex &b, const Vertex &c);
	Triangle(const Triangle &t);
	~Triangle();

	Triangle& operator=(const Triangle &rhs);

	float				area() const;
	bool				intersected(const Ray &ray, float &t) const;

private:
	Vertex				a;
	Vertex				b;
	Vertex				c;
};

#endif
