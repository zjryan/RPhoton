#include "Cube.h"
#include "Texture.h"
#include "Utilities.h"


Cube::Cube(const Point &center, float edge)
	: Geometry(),
		Bl(center - edge / 2),
		Bh(center + edge / 2)
{
}

Cube::Cube(const Point &p1, const Point &p2)
	:	Geometry(),
		Bl(min(p1.x, p2.x), min(p1.y, p2.y), min(p1.z, p2.z)),
		Bh(max(p1.x, p2.x), max(p1.y, p2.y), max(p1.z, p2.z))
{
}

Cube::Cube(const Cube &c)
	:	Geometry(c),
		Bl(c.Bl),
		Bh(c.Bh)
{
}

Cube::~Cube()
{
}

Vector2 Cube::texCoord(const Ray &ray, float &t) const
{
	//assume all the skyboxes are cube
	Face f = intersectFace(ray, t);
	Point hitPoint(ray.o + ray.d * t);
	//edge length
	float el = Bh.x - Bl.x;
	//half edge length
	float hl = el / 2;
	Vector2 texcoord;
	float u;
	float v;
	switch(f)
	{
	case px:
		u = (hl - hitPoint.y) / el;
		v = (hl + hitPoint.z) / el;
		texcoord = Vector2(u, v);
		break;

	case nx:
		u = (hl + hitPoint.y) / el;
		v = (hl + hitPoint.z) / el;
		texcoord = Vector2(u, v);
		break;

	case py:
		u = (hl + hitPoint.x) / el;
		v = (hl + hitPoint.z) / el;
		texcoord = Vector2(u, v);
		break;

	case ny:
		u = (hl - hitPoint.x) / el;
		v = (hl + hitPoint.z) / el;
		texcoord = Vector2(u, v);
		break;

	case pz:
		u = (hl + hitPoint.x) / el;
		v = (hl + hitPoint.y) / el;
		texcoord = Vector2(u, v);
		break;

	case nz:
		u = (hl - hitPoint.x) / el;
		v = (hl - hitPoint.y) / el;
		texcoord = Vector2(u, v);
		break;

	default:
		break;
	}

	return texcoord;
}

bool Cube::intersected(const Ray &ray, float &t) const
{
	float tfar	=  INFINITY;
	float tnear =  -INFINITY;

	for (auto i = 0; i < 3; i++)
	{
		if(floatEqual(ray.d[i], 0.0f))
		{
			if (ray.o[i] < Bl[i] || ray.o[i] > Bh[i])
			{
				return false;
			}
		}
		else
		{
			float t1 = (Bl[i] - ray.o[i]) / ray.d[i];
			float t2 = (Bh[i] - ray.o[i]) / ray.d[i];

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
	if (tnear < t)
	{
		t = tnear;
	}

	return true;
}

Normal Cube::normal(const Ray &ray, float &t) const
{
	Face f = intersectFace(ray, t);
	Normal n;
	switch(f)
	{
	case px:
		n = Normal(1.0f, 0.0f, 0.0f);
		break;
	case nx:
		n = Normal(-1.0f, 0.0f, 0.0f);
		break;
	case py:
		n = Normal(0.0f, 1.0f, 0.0f);
		break;
	case ny:
		n = Normal(0.0f, -1.0f, 0.0f);
		break;
	case pz:
		n = Normal(0.0f, 0.0f, 1.0f);
		break;
	case nz:
		n = Normal(0.0f, 0.0f, -1.0f);
		break;
	default:
		break;
	}

	return n;
}

Cube::Face Cube::intersectFace(const Ray &ray, float t) const
{
	Point	center((Bl + Bh) / 2);
	Point	intersect(ray.o + ray.d * t);
	Vector3	distance(Bh - center);
	Vector3	d(intersect - center);

	Face f;
	for (auto i = 0; i < 3; i++)
	{
		if (floatEqual(d[i], distance[i]))
		{
			switch (i)
			{
			case 0:
				f = px;
				break;
			case 1:
				f = py;
				break;
			case 2:
				f = pz;
				break;
			default:
				break;
			}
			break;
		}

		if (floatEqual(d[i], -distance[i]))
		{
			switch (i)
			{
			case 0:
				f = nx;
				break;
			case 1:
				f = ny;
				break;
			case 2:
				f = nz;
				break;
			default:
				break;
			}
		}
	}
	return f;
}

SkyBox::SkyBox()
	:	Cube(Point( 10000.0f,  10000.0f,  10000.0f),
			 Point(-10000.0f, -10000.0f, -10000.0f))
{
	initializeSky();
}

SkyBox::SkyBox(const Point &p1, const Point &p2)
	:	Cube(p1, p2)
{
	initializeSky();
}

SkyBox::~SkyBox()
{
	Memory::safeDelete(px);
	Memory::safeDelete(nx);
	Memory::safeDelete(py);
	Memory::safeDelete(ny);
	Memory::safeDelete(pz);
	Memory::safeDelete(nz);
}

Normal SkyBox::normal(const Ray &ray, float &t) const
{
	Normal n = Cube::normal(ray, t);
	return -n;
}

Color SkyBox::skyColor(const Ray &ray) const
{
	Color retColor;
	float t = INFINITY;
	intersected(ray, t);
	auto texture = faceTexture(ray, t);
	auto texcoord = texCoord(ray, t);
	retColor = texture->Sample(texcoord);
	return retColor;
}

Texture* SkyBox::faceTexture(const Ray &ray, float t) const
{
	Face f = intersectFace(ray, t);
	Texture *tex = nullptr;
	switch(f)
	{
	case Face::px:
		tex = px;
		break;

	case Face::nx:
		tex = nx;
		break;

	case Face::py:
		tex = py;
		break;

	case Face::ny:
		tex = ny;
		break;

	case Face::pz:
		tex = pz;
		break;

	case Face::nz:
		tex = nz;
		break;
	}

	return tex;
}

void SkyBox::initializeSky()
{
	px = new Texture(L"Texture/SkyBox/+x.bmp", Texture::None);
	nx = new Texture(L"Texture/SkyBox/-x.bmp", Texture::None);
	py = new Texture(L"Texture/SkyBox/+y.bmp", Texture::None);
	ny = new Texture(L"Texture/SkyBox/-y.bmp", Texture::None);
	pz = new Texture(L"Texture/SkyBox/+z.bmp", Texture::None);
	nz = new Texture(L"Texture/SkyBox/-z.bmp", Texture::None);
}
