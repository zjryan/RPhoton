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

	Vector2			texCoord(const Ray &ray, float &t) const override;
	bool			intersected(const Ray &ray, float &t) const override;
	virtual Normal	normal(const Ray &ray, float &t) const override;

protected:
	enum Face
	{
		px, nx, py, ny, pz, nz
	};

	Face			intersectFace(const Ray &ray, float t) const;

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

	Normal			normal(const Ray &ray, float &t) const override;
	Color			skyColor(const Ray &ray) const;
	Texture*		faceTexture(const Ray &ray, float t) const;
	void			initializeSky();

private:
	Texture			*px, *nx, *py, *ny, *pz, *nz;
};

#endif
