#ifndef ZJR_AABB_
#define ZJR_AABB_

#include <math.h>
#include "./Maths.h"
#include "./Point.h"
#include "./Ray.h"

using namespace Math;

class AABB
{
public:
	Point				minPoint;
	Point				maxPoint;

	AABB();
	AABB(const Point &p);
	AABB(const Point &p1, const Point &p2);
	AABB(const AABB &b);
	~AABB();

	bool				overlaps(const AABB &b) const;
	bool				inside(const Point &pt) const;
	bool				intersected(const Ray &ray) const;
	float 				surfaceArea() const;
	float				volume() const;
	int					maximumExtent() const;
	Point				lerp(float tx, float ty, float tz) const;
	Vector3				offset(const Point &p) const;
	void				expand(float delta);

	void				revise(const Point &p);
};

inline AABB::AABB()
	:	minPoint( INFINITY,  INFINITY,  INFINITY),
		maxPoint(-INFINITY, -INFINITY, -INFINITY)
{
}

inline AABB::AABB(const Point &p)
	:	minPoint(p),
		maxPoint(p)
{
}

inline AABB::AABB(const Point &p1, const Point &p2)
{
	minPoint = Point(min(p1.x, p2.x), min(p1.y, p2.y), min(p1.z, p2.z));
	maxPoint = Point(max(p1.x, p2.x), max(p1.y, p2.y), max(p1.z, p2.z));
}

inline AABB::AABB(const AABB &b)
	:	minPoint(b.minPoint),
		maxPoint(b.maxPoint)
{
}

inline AABB::~AABB()
{
}

inline bool AABB::overlaps(const AABB &b) const
{
	bool x = maxPoint.x >= b.minPoint.x && minPoint.x <= b.maxPoint.x;
	bool y = maxPoint.y >= b.minPoint.y && minPoint.y <= b.maxPoint.y;
	bool z = maxPoint.z >= b.minPoint.z && minPoint.z <= b.maxPoint.z;
	return x && y && z;
}

inline bool AABB::inside(const Point &pt) const
{
	return  pt.x >= minPoint.x && pt.x <= maxPoint.x &&
			pt.y >= minPoint.y && pt.y <= maxPoint.y &&
			pt.z >= minPoint.z && pt.z <= maxPoint.z;
}

inline bool AABB::intersected(const Ray &ray) const
{
	float tfar = INFINITY;
	float tnear = -INFINITY;

	for (auto i = 0; i < 3; i++)
	{
		if (floatEqual(ray.d[i], 0.0f))
		{
			if (ray.o[i] < minPoint[i] || ray.o[i] > maxPoint[i])
			{
				return false;
			}
		}
		else
		{
			float t1 = (minPoint[i] - ray.o[i]) / ray.d[i];
			float t2 = (maxPoint[i] - ray.o[i]) / ray.d[i];

			if (t1 > t2)
			{
				swap(t1, t2);
			}
			if (t1 > tnear)
			{
				tnear = t1;
			}
			if (t2 < tfar)
			{
				tfar = t2;
			}
			if (tnear > tfar)
			{
				return false;
			}
		}
	}

	return true;
}

inline float AABB::surfaceArea() const
{
	Vector3 d = maxPoint - minPoint;
	return 2.0f * (d.x * d.y + d.x * d.z + d.y * d.z);
}

inline float AABB::volume() const
{
	Vector3 d = maxPoint - minPoint;
	return d.x * d.y * d.z;
}

inline int AABB::maximumExtent() const
{
	Vector3 diag = maxPoint - minPoint;
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
	return Point(Math::lerp(tx, minPoint.x, maxPoint.x),
				 Math::lerp(ty, minPoint.y, maxPoint.y),
				 Math::lerp(tz, minPoint.z, maxPoint.z));
}

inline Vector3 AABB::offset(const Point &p) const
{
	return Vector3((p.x - minPoint.x) / (maxPoint.x - minPoint.x),
				   (p.y - minPoint.y) / (maxPoint.y - minPoint.y),
				   (p.z - minPoint.z) / (maxPoint.z - minPoint.z));
}

inline void AABB::expand(float delta)
{
	minPoint -= Point(delta, delta, delta);
	minPoint += Point(delta, delta, delta);
}

inline void AABB::revise(const Point &p)
{
	int x = p.x;
	int y = p.y;
	int z = p.z;

	if (x < minPoint.x)
	{
		minPoint.x = x;
	}

	if (x > maxPoint.x)
	{
		maxPoint.x = x;
	}

	if (y < minPoint.y)
	{
		minPoint.y = y;
	}

	if (y > maxPoint.y)
	{
		maxPoint.y = y;
	}

	if (z < minPoint.z)
	{
		minPoint.z = z;
	}

	if (z > maxPoint.z)
	{
		maxPoint.z = z;
	}
}

#endif
