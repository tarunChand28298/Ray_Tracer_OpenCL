#pragma once
#include <CL/cl.h>

class Display;
class Scene;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Initialize(Display& const display, Scene& const scene);
	void Render();
	void ShutDown();

private:
	Scene* sourceScene;
	Display* targetDisplay;

	cl_device_id device;
	cl_context context;
	cl_command_queue commandQueue;

	cl_program program;
	cl_kernel kernel;

	cl_mem meshArrayBuffer;
	cl_mem meshXformArrayBuffer;
	cl_mem indexArrayBuffer;
	cl_mem vertexArrayBuffer;
	cl_mem resultBuffer;

};
