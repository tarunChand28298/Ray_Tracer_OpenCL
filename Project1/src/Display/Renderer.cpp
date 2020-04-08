#include "Renderer.h"
#include "Display.h"
#include "../Scene/Scene.h"

#include <iostream>
#include <sstream>
#include <fstream>

const char* getErrorString(cl_int error)
{
	switch (error) {
		// run-time and JIT compiler errors
	case  0: return "CL_SUCCESS";
	case -1: return "CL_DEVICE_NOT_FOUND";
	case -2: return "CL_DEVICE_NOT_AVAILABLE";
	case -3: return "CL_COMPILER_NOT_AVAILABLE";
	case -4: return "CL_MEM_OBJECT_ALLOCATION_FAILURE";
	case -5: return "CL_OUT_OF_RESOURCES";
	case -6: return "CL_OUT_OF_HOST_MEMORY";
	case -7: return "CL_PROFILING_INFO_NOT_AVAILABLE";
	case -8: return "CL_MEM_COPY_OVERLAP";
	case -9: return "CL_IMAGE_FORMAT_MISMATCH";
	case -10: return "CL_IMAGE_FORMAT_NOT_SUPPORTED";
	case -11: return "CL_BUILD_PROGRAM_FAILURE";
	case -12: return "CL_MAP_FAILURE";
	case -13: return "CL_MISALIGNED_SUB_BUFFER_OFFSET";
	case -14: return "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST";
	case -15: return "CL_COMPILE_PROGRAM_FAILURE";
	case -16: return "CL_LINKER_NOT_AVAILABLE";
	case -17: return "CL_LINK_PROGRAM_FAILURE";
	case -18: return "CL_DEVICE_PARTITION_FAILED";
	case -19: return "CL_KERNEL_ARG_INFO_NOT_AVAILABLE";

		// compile-time errors
	case -30: return "CL_INVALID_VALUE";
	case -31: return "CL_INVALID_DEVICE_TYPE";
	case -32: return "CL_INVALID_PLATFORM";
	case -33: return "CL_INVALID_DEVICE";
	case -34: return "CL_INVALID_CONTEXT";
	case -35: return "CL_INVALID_QUEUE_PROPERTIES";
	case -36: return "CL_INVALID_COMMAND_QUEUE";
	case -37: return "CL_INVALID_HOST_PTR";
	case -38: return "CL_INVALID_MEM_OBJECT";
	case -39: return "CL_INVALID_IMAGE_FORMAT_DESCRIPTOR";
	case -40: return "CL_INVALID_IMAGE_SIZE";
	case -41: return "CL_INVALID_SAMPLER";
	case -42: return "CL_INVALID_BINARY";
	case -43: return "CL_INVALID_BUILD_OPTIONS";
	case -44: return "CL_INVALID_PROGRAM";
	case -45: return "CL_INVALID_PROGRAM_EXECUTABLE";
	case -46: return "CL_INVALID_KERNEL_NAME";
	case -47: return "CL_INVALID_KERNEL_DEFINITION";
	case -48: return "CL_INVALID_KERNEL";
	case -49: return "CL_INVALID_ARG_INDEX";
	case -50: return "CL_INVALID_ARG_VALUE";
	case -51: return "CL_INVALID_ARG_SIZE";
	case -52: return "CL_INVALID_KERNEL_ARGS";
	case -53: return "CL_INVALID_WORK_DIMENSION";
	case -54: return "CL_INVALID_WORK_GROUP_SIZE";
	case -55: return "CL_INVALID_WORK_ITEM_SIZE";
	case -56: return "CL_INVALID_GLOBAL_OFFSET";
	case -57: return "CL_INVALID_EVENT_WAIT_LIST";
	case -58: return "CL_INVALID_EVENT";
	case -59: return "CL_INVALID_OPERATION";
	case -60: return "CL_INVALID_GL_OBJECT";
	case -61: return "CL_INVALID_BUFFER_SIZE";
	case -62: return "CL_INVALID_MIP_LEVEL";
	case -63: return "CL_INVALID_GLOBAL_WORK_SIZE";
	case -64: return "CL_INVALID_PROPERTY";
	case -65: return "CL_INVALID_IMAGE_DESCRIPTOR";
	case -66: return "CL_INVALID_COMPILER_OPTIONS";
	case -67: return "CL_INVALID_LINKER_OPTIONS";
	case -68: return "CL_INVALID_DEVICE_PARTITION_COUNT";

	default: return "Unknown OpenCL error";
	}
}

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Initialize(const Display& display)
{
	width = display.width;
	height = display.height;

	//Create device, context and command queue:
	{
		//Device:
		cl_platform_id* platformIDs;
		cl_uint platforms;
		clGetPlatformIDs(1, nullptr, &platforms);
		platformIDs = new cl_platform_id[platforms];
		clGetPlatformIDs(platforms, platformIDs, nullptr);

		clGetDeviceIDs(platformIDs[0], CL_DEVICE_TYPE_GPU, 1, &device, NULL);

		delete[] platformIDs;

		//Context:
		context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);

		//Command queue:
		commandQueue = clCreateCommandQueue(context, device, (cl_command_queue_properties)0, NULL);
	}

	//Compile source and create kernel:
	{
		std::ifstream sourceFile("E:\\Projects\\GamedevProjects\\GameEngineProjects\\Solution3\\Project1\\shaders\\shader.cl");
		std::string sourceTextString((std::istreambuf_iterator<char>(sourceFile)), std::istreambuf_iterator<char>());
		const char* sourceText = sourceTextString.c_str();

		program = clCreateProgramWithSource(context, 1, &sourceText, NULL, NULL);
		auto result = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
		
		//Error checking in source:
		if (result == CL_BUILD_PROGRAM_FAILURE) 
		{
			size_t logSize;
			clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
		
			char* log = new char[logSize];
			clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, logSize, log, NULL);
			std::cout << log << std::endl;

			delete[] log;
		}

		kernel = clCreateKernel(program, "GPUMain", NULL);
	}

	//Setup inputs and outputs:
	{
		camXformBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(Matrix4x4), NULL, NULL);
		invCamProjMatBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(Matrix4x4), NULL, NULL);
		triangleXformBuffer = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(Matrix4x4), NULL, NULL);
		verticiesBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(Vector) * 3, NULL, NULL);
		resultBuffer = clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(cl_int) * width * height, NULL, NULL);
	}

	if (result != nullptr) delete[] result;
	result = new int[display.width * display.height];
}

void Renderer::Render(const Scene& scene)
{
	clEnqueueWriteBuffer(commandQueue, verticiesBuffer, CL_TRUE, 0, sizeof(Vector) * 3, scene.triangle, 0, NULL, NULL);

	clSetKernelArg(kernel, 0, sizeof(Matrix4x4), &scene.camXform);
	clSetKernelArg(kernel, 1, sizeof(Matrix4x4), &scene.invProjection);
	clSetKernelArg(kernel, 2, sizeof(Matrix4x4), &scene.triangleXform);
	clSetKernelArg(kernel, 3, sizeof(verticiesBuffer), &verticiesBuffer);
	clSetKernelArg(kernel, 4, sizeof(resultBuffer), &resultBuffer);
	clSetKernelArg(kernel, 5, sizeof(int), &width);
	clSetKernelArg(kernel, 6, sizeof(int), &height);

	size_t globalDimensions[] = { width * height, 0, 0 };
	auto returnValue = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, globalDimensions, NULL, 0, NULL, NULL);
	if (returnValue != CL_SUCCESS)
	{
		const char* errorString = getErrorString(returnValue);
		std::cerr << errorString << std::endl;
	}

	clEnqueueReadBuffer(commandQueue, resultBuffer, CL_FALSE, 0, sizeof(cl_int) * width * height, (void*)result, 0, NULL, NULL);

	clFinish(commandQueue);
}

void Renderer::ShutDown()
{
	clReleaseMemObject(camXformBuffer);
	clReleaseMemObject(invCamProjMatBuffer);
	clReleaseMemObject(triangleXformBuffer);
	clReleaseMemObject(verticiesBuffer);
	clReleaseMemObject(resultBuffer);

	clReleaseCommandQueue(commandQueue);
	clReleaseProgram(program);
	clReleaseContext(context);

	if (result != nullptr)
	{
		delete[] result;
		result = nullptr;
	}
}

int* Renderer::GetResult()
{
	return result;
}
