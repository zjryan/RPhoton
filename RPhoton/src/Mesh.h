#ifndef ZJR_MESH_
#define ZJR_MESH_

#include <vector>
#include "Triangle.h"
#include "../Parser/MeshLoader.h"

class Mesh
{
public:
	typedef std::vector<Triangle>	TriangleList;

	Mesh(std::string meshPath);
	~Mesh();

private:
	MeshLoader::VertexArray			vertexbuffer;
	TriangleList					triangle;

};

#endif
