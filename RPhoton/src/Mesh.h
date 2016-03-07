#ifndef ZJR_MESH_
#define ZJR_MESH_

#include <vector>
#include "Geometry.h"
#include "Triangle.h"
#include "../GraphicLib/AABB.h"

class Mesh : public Geometry
{
public:
	typedef std::vector<Triangle>	TriangleList;

	Mesh(std::string meshPath);
	~Mesh();

	Vector2							texCoord(const Ray &ray, float &t) const override;
	bool							intersected(const Ray &ray, float &t) const override;
	Normal							normal(const Ray &ray, float &t) const override;
	void							transform();

	int								vertexSize() const;
	int								triangleSize() const;
	const std::vector<Vertex>&		vertexBuffer() const;
	const TriangleList&				triangleList() const;

private:
	void							importMesh(std::string meshPath);
	void							updateBounding(const Point &p);

private:
	std::vector<Vertex>				vertexbuffer;
	TriangleList					triangles;
	int								trianglesNum;
	int								vertexNum;
	AABB							aabb;
};

inline int Mesh::vertexSize() const
{
	return vertexNum;
}

inline int Mesh::triangleSize() const
{
	return trianglesNum;
}

inline const std::vector<Vertex>& Mesh::vertexBuffer() const
{
	return vertexbuffer;
}

inline const Mesh::TriangleList& Mesh::triangleList() const
{
	return triangles;
}
#endif
