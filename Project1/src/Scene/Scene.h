#pragma once

#include "../Math/Math.h"

class Scene
{
public:
	Vector triangle[3];
	Matrix4x4 triangleXform;

	Matrix4x4 camXform;
	Matrix4x4 invProjection;

	float fov = 160.0f;
};
