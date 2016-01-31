#ifndef ZJR_BBOX_
#define ZJR_BBOX_

#include <math.h>
#include "./Maths.h"
#include "./Point.h"

using namespace Math;

class AABB
{
public:
	Point				pMin;
	Point				pMax;

	AABB();
	AABB(const Point &p);
	AABB(const Point &p1, const Point &p2);
	AABB(const AABB &b);
	~AABB();

	bool				overlaps(const AABB &b) const;
	bool				inside(const Point &pt) const;
	float 				surfaceArea() const;
	float				volume() const;
	int					maximumExtent() const;
	Point				lerp(float tx, float ty, float tz) const;
	Vector3				offset(const Point &p) const;
	void				expand(float delta);

	static AABB			Union(const AABB &b, const Point &p);
};

inline AABB::AABB()
	:	pMin(-INFINITY, -INFINITY, -INFINITY),
		pMax( INFINITY,  INFINITY,  INFINITY)
{
}

inline AABB::AABB(const Point &p)
	:	pMin(p),
		pMax(p)
{
}

inline AABB::AABB(const Point &p1, const Point &p2)
{
	pMin = Point(min(p1.x, p2.x), min(p1.y, p2.y), min(p1.z, p2.z));
	pMax = Point(max(p1.x, p2.x), max(p1.y, p2.y), max(p1.z, p2.z));
}

inline AABB::AABB(const AABB &b)
	:	pMin(b.pMin),
		pMax(b.pMax)
{
}

inline AABB::~AABB()
{
}

inline bool AABB::overlaps(const AABB &b) const
{
	bool x = pMax.x >= b.pMin.x && pMin.x <= b.pMax.x;
	bool y = pMax.y >= b.pMin.y && pMin.y <= b.pMax.y;
	bool z = pMax.z >= b.pMin.z && pMin.z <= b.pMax.z;
	return x && y && z;
}

inline bool AABB::inside(const Point &pt) const
{
	return  pt.x >= pMin.x && pt.x <= pMax.x &&
			pt.y >= pMin.y && pt.y <= pMax.y &&
			pt.z >= pMin.z && pt.z <= pMax.z;
}

inline float AABB::surfaceArea() const
{
	Vector3 d = pMax - pMin;
	return 2.0f * (d.x * d.y + d.x * d.z + d.y * d.z);
}

inline float AABB::volume() const
{
	Vector3 d = pMax - pMin;
	return d.x * d.y * d.z;
}

inline int AABB::maximumExtent() const
{
	Vector3 diag = pMax - pMin;
	if (diag.x > diag.y && diag.x > diag.z)
	{
		return 0;
	}
	else if (diag.y > diag.z)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

inline Point AABB::lerp(float tx, float ty, float tz) const
{
	return Point(Math::lerp(tx, pMin.x, pMax.x),
				 Math::lerp(ty, pMin.y, pMax.y),
				 Math::lerp(tz, pMin.z, pMax.z));
}

inline Vector3 AABB::offset(const Point &p) const
{
	return Vector3((p.x - pMin.x) / (pMax.x - pMin.x),
				   (p.y - pMin.y) / (pMax.y - pMin.y),
				   (p.z - pMin.z) / (pMax.z - pMin.z));
}

inline void AABB::expand(float delta)
{
	pMin -= Point(delta, delta, delta);
	pMin += Point(delta, delta, delta);
}

inline AABB AABB::Union(const AABB &b, const Point &p)
{
	AABB ret(b);
	ret.pMin.x = min(b.pMin.x, p.x);
	ret.pMin.y = min(b.pMin.y, p.y);
	ret.pMin.z = min(b.pMin.z, p.z);
	ret.pMax.x = max(b.pMax.x, p.x);
	ret.pMax.y = max(b.pMax.y, p.y);
	ret.pMax.z = max(b.pMax.z, p.z);
	return ret;
}

#endif
