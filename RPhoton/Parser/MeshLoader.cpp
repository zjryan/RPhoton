#include "MeshLoader.h"

using namespace std;

MeshLoader::MeshLoader(string MeshPath)
	:	Parser(MeshPath)
{
	ifstream	mesh(path);
	string		line, ignore;
	getline(mesh, line);

	//get vertices size
	istringstream vb(line);
	vb >> ignore;
	vb >> verticesSize;

	//get indices size
	getline(mesh, line);
	istringstream ib(line);
	ib >> ignore;
	ib >> trianglesSize;

	mesh.close();
}

MeshLoader::~MeshLoader()
{
}

void MeshLoader::LoadVertices(VertexArray &vb)
{
	ifstream	mesh(path);
	string		line, data;
	MoveTo(mesh, "vertices");
	
	for (auto i = 0; i < verticesSize; i++)
	{
		istringstream record;

		record >> data;
		vb[i].position.x = atof(data.c_str());
		record >> data;
		vb[i].position.y = atof(data.c_str());
		record >> data;
		vb[i].position.z = atof(data.c_str());

		record >> data;
		vb[i].normal.x = atof(data.c_str());
		record >> data;
		vb[i].normal.y = atof(data.c_str());
		record >> data;
		vb[i].normal.z = atof(data.c_str());

		record >> data;
		vb[i].texCoord.x = atof(data.c_str());
		record >> data;
		vb[i].texCoord.y = atof(data.c_str());
	}

	mesh.close();
}

void MeshLoader::LoadIndices(IndexArray &ib)
{
	ifstream	mesh(path);
	string		line, data;
	MoveTo(mesh, "indices");

	auto indicesSize = trianglesSize * 3;
	for (auto i = 0; i < indicesSize; i++)
	{
		istringstream record;
		record >> data;
		ib[i] = atoi(data.c_str());
	}

	mesh.close();
}

size_t MeshLoader::VertexArraySize() const
{
	return verticesSize;
}

size_t MeshLoader::IndexArraySize() const
{
	return trianglesSize;
}

void MeshLoader::MoveTo(ifstream &file, string keyword) const
{
	string		line, word;
	while(getline(file, line))
	{
		istringstream record;
		record >> word;
		if(word == "#")
		{
			record >> word;
			if(word == keyword)
			{
				break;
			}
		}
	}
}
