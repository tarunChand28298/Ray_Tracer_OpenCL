#pragma once
#include <CL/cl.h>

class Display;
class Scene;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Initialize(const Display& display);
	void Render(const Scene& scene);
	void ShutDown();

	int* GetResult();

private:
	int* result = nullptr;
	int width;
	int height;

	cl_device_id device;
	cl_context context;
	cl_command_queue commandQueue;

	cl_program program;
	cl_kernel kernel;

	cl_mem camXformBuffer;
	cl_mem invCamProjMatBuffer;
	cl_mem triangleXformBuffer;
	cl_mem verticiesBuffer;
	cl_mem resultBuffer;

};
