#ifndef ZJR_MESHLOADER_
#define ZJR_MESHLOADER_

#include "Parser.h"
#include "../GraphicLib/Point.h"
#include "../GraphicLib/Normal.h"
#include "../src/Texture.h"

class MeshLoader : public Parser
{
public:
	typedef std::vector<Vertex>		VertexArray;
	typedef std::vector<size_t>		IndexArray;

	MeshLoader(std::string MeshPath);
	~MeshLoader();

	void				LoadVertices(VertexArray &vb);
	void				LoadIndices(IndexArray &ib);

	size_t				VertexArraySize() const;
	size_t				IndexArraySize() const;

private:
	void				MoveTo(std::ifstream &file, std::string keyword) const;

private:
	size_t				verticesSize;
	size_t				trianglesSize;
};

#endif
