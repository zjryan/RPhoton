#ifndef ZJR_MESH_
#define ZJR_MESH_

#include <vector>
#include "Triangle.h"
#include "../Parser/MeshLoader.h"

class Mesh : public Geometry
{
public:
	typedef std::vector<Triangle>	TriangleList;

	Mesh(std::string meshPath);
	~Mesh();

private:
	void							importMesh(std::string meshPath);

private:
	MeshLoader::VertexArray			vertexbuffer;
	TriangleList					triangles;

};

#endif
