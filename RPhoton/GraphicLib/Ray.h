#ifndef ZJR_RAY_
#define ZJR_RAY_

#include "./Vector3.h"
#include "./Point.h"

class Ray
{
public:
	Point				o;
	Vector3				d;
	int					depth;

	Ray();
	Ray(const Point &origin, const Vector3 &direction, int d = 0);
	Ray(const Ray &r);
	~Ray();

	Point				operator()(float t) const;

};

inline Ray::Ray()
	:	o(),
		d(),
		depth(0)
{
}

inline Ray::Ray(const Point &origin, const Vector3 &direction, int d /*= 0*/)
	:	o(origin),
		d(direction),
		depth(d)
{
}

inline Ray::Ray(const Ray &r)
	:	o(r.o),
		d(r.d),
		depth(r.depth)
{
}

inline Ray::~Ray()
{
}

inline Point Ray::operator()(float t) const
{
	return o + d * t;
}

#endif
