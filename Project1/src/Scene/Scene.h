#pragma once

#include "../Math/Math.h"
#include <vector>

struct Mesh
{
	int transformIndex;
	int startTriangleIndex;
	int endTriangleIndex;

	Mesh(int tid, int sid, int eid) :transformIndex(tid), startTriangleIndex(sid), endTriangleIndex(eid) {}
};

struct Index
{
	int vertex0;
	int vertex1;
	int vertex2;

	Colour albedo;
	Colour specular;

	Index(int v0, int v1, int v2, Colour a, Colour s) :vertex0(v0), vertex1(v1), vertex2(v2), albedo(a), specular(s) {}
};

class Scene
{
public:
	std::vector<Mesh> meshArray;
	std::vector<Matrix4x4> meshXformArray;
	std::vector<Index> indexArray;
	std::vector<Vector> verticies;

	Matrix4x4 camXform;
	Matrix4x4 invProjection;
	float fov = 160.0f;
};
