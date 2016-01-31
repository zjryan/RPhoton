#include "Mesh.h"
#include "Triangle.h"
#include <fstream>

using namespace std;

Mesh::Mesh(string meshPath)
	:	Geometry(),
		vertexbuffer(),
		triangles(),
		vertexNum(0),
		trianglesNum(0)
{
	importMesh(meshPath);
}

Mesh::~Mesh()
{
	vertexbuffer.clear();
	triangles.clear();
}

Vector2 Mesh::texCoord(const Ray &ray, float &t) const
{
	return Vector2();
}

bool Mesh::intersected(const Ray &ray, float &t) const
{
	return true;
}

Normal Mesh::normal(const Ray &ray, float &t) const
{
	return Normal();
}

void Mesh::importMesh(string meshPath)
{
	ifstream MeshFile(meshPath);
	string ignore;

	MeshFile >> ignore >> vertexNum;
	MeshFile >> ignore >> trianglesNum;

	MeshFile >> ignore >> ignore >> ignore >> ignore;

	vertexbuffer.resize(vertexNum);
	for (int i = 0; i < vertexNum; i++)
	{
		MeshFile >> vertexbuffer[i].position.x
				 >> vertexbuffer[i].position.y
				 >> vertexbuffer[i].position.z;

		MeshFile >> vertexbuffer[i].normal.x
				 >> vertexbuffer[i].normal.y
				 >> vertexbuffer[i].normal.z;
	}
	
	MeshFile >> ignore >> ignore >> ignore;

	triangles.resize(trianglesNum);
	for (int i = 0; i < trianglesNum; i++)
	{
		int t1, t2, t3;
		MeshFile >> t1 >> t2 >> t3;
		triangles[i] = Triangle(vertexbuffer[t1], vertexbuffer[t2], vertexbuffer[t3]);
	}

	MeshFile.close();
}
 