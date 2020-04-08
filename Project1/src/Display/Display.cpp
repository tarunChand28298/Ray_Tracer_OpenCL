#include "Display.h"

Display::Display()
{
}

Display::~Display()
{
}

void Display::Initialize()
{
	//Create window:
	windowClassInfo.style = CS_OWNDC;
	windowClassInfo.lpfnWndProc = MainWindowProcedure;
	windowClassInfo.cbClsExtra = 0;
	windowClassInfo.cbWndExtra = 0;
	windowClassInfo.hInstance = GetModuleHandle(0);
	windowClassInfo.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	windowClassInfo.hCursor = LoadCursor(nullptr, IDC_ARROW);
	windowClassInfo.hbrBackground = nullptr;
	windowClassInfo.lpszMenuName = 0;
	windowClassInfo.lpszClassName = "MainWindowClassName";
	RegisterClass(&windowClassInfo);

	windowHandle = CreateWindow("MainWindowClassName", "Ray Tracer", WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, width + 16, height + 39, nullptr, nullptr, GetModuleHandle(0), this);
	ShowWindow(windowHandle, SW_SHOW);

	//Create pixelbuffer:
	pixelbufferInfo.bmiHeader.biSize = sizeof(pixelbufferInfo.bmiHeader);
	pixelbufferInfo.bmiHeader.biWidth = width;
	pixelbufferInfo.bmiHeader.biHeight = height;
	pixelbufferInfo.bmiHeader.biPlanes = 1;
	pixelbufferInfo.bmiHeader.biBitCount = sizeof(int) * 8;
	pixelbufferInfo.bmiHeader.biCompression = BI_RGB;

	if (pixelBuffer != nullptr) { delete[] pixelBuffer; }
	pixelBuffer = new int[width * height];
	ClearPixelbuffer();
}

void Display::PollEvents()
{
	MSG message = {};
	while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

void Display::Shutdown()
{
	UnregisterClass("MainWindowClassName", GetModuleHandle(0));
	if (pixelBuffer != nullptr)
	{
		delete[] pixelBuffer;
		pixelBuffer = nullptr;
	}
}

void Display::PutPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char p)
{
	if (x < 0 || x >= width || y < 0 || y >= height) { return; }

	int index = 0;
	int colour = 0;

	//calculate colour:
	colour = p;
	colour <<= 8;
	colour |= r;
	colour <<= 8;
	colour |= g;
	colour <<= 8;
	colour |= b;

	//calculate index:
	index = (width * y) + x;

	//Write to pixelbuffer:
	pixelBuffer[index] = colour;
}

void Display::PutPixel(int x, int y, int colour)
{
	if (x < 0 || x >= width || y < 0 || y >= height) { return; }
	pixelBuffer[(width * y) + x] = colour;
}

void Display::FlipFromIntPtr(int* source)
{
	memcpy(pixelBuffer, source, sizeof(int) * width * height);
}

void Display::ClearPixelbuffer()
{
	for (int i = 0; i < height * width; i++)
	{
		pixelBuffer[i] = clearColour;
	}
}

void Display::PresentPixelbufferToWindow()
{
	HDC currentDeviceContext = GetDC(windowHandle);
	StretchDIBits(currentDeviceContext, 0, 0, width, height, 0, 0, width, height, pixelBuffer, &pixelbufferInfo, DIB_RGB_COLORS, SRCCOPY);
	ReleaseDC(windowHandle, currentDeviceContext);
}

LRESULT Display::MainWindowProcedure(HWND windowHandle, UINT message, WPARAM wparam, LPARAM lparam)
{
	static Display* displayInstance = nullptr;
	switch (message)
	{
	case WM_CREATE: {
		displayInstance = (Display*)((LPCREATESTRUCT)lparam)->lpCreateParams;
		displayInstance->quitRequested = false;
		break;
	}
	case WM_CLOSE: {
		displayInstance->quitRequested = true;
		DestroyWindow(windowHandle);
		break;
	}
	default: {
		break;
	}
	}

	return DefWindowProc(windowHandle, message, wparam, lparam);
}
