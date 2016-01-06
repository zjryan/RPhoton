#ifndef ZJR_CUBE_
#define ZJR_CUBE_

#include "Geometry.h"
#include "../GraphicLib/Point.h"
#include "../GraphicLib/Normal.h"
#include "../GraphicLib/Ray.h"

class Texture;
class Color;

class Cube : public Geometry
{
public:
	Cube(const Point &center, float edge);
	Cube(const Point &p1, const Point &p2);
	Cube(const Cube &c);
	~Cube();

	Vector2			GetTexCoord(const Ray &ray, float &t) const override;
	bool			Intersect(const Ray &ray, float &t) const override;
	virtual Normal	GetNormal(const Ray &ray, float &t) const override;

protected:
	enum Face
	{
		px, nx, py, ny, pz, nz
	};

	Face			IntersectFace(const Ray &ray, float t) const;

protected:
	Point			Bl;
	Point			Bh;
};

class SkyBox : public Cube
{
public:
	SkyBox();
	SkyBox(const Point &p1, const Point &p2);
	~SkyBox();

	Normal			GetNormal(const Ray &ray, float &t) const override;
	Color			GetSkyColor(const Ray &ray) const;
	Texture*		GetFaceTexture(const Ray &ray, float t) const;
	void			InitializeSky();

private:
	Texture			*px, *nx, *py, *ny, *pz, *nz;
};

#endif
