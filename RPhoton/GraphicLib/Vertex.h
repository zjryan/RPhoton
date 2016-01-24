#ifndef ZJR_VERTEX_
#define ZJR_VERTEX_

#include "Point.h"
#include "Normal.h"
#include "Vector2.h"

class Vertex
{
public:
	Point				position;
	Normal				normal;
	Vector2				texCoord;

	Vertex();
	Vertex(const Vertex &v);
	~Vertex();
};

inline Vertex::Vertex()
	:	position(),
		normal(),
		texCoord()
{
}

inline Vertex::Vertex(const Vertex &v)
	:	position(v.position),
		normal(v.normal),
		texCoord(v.texCoord)
{
}

inline Vertex::~Vertex()
{
}

#endif
