#pragma once
#include <Windows.h>

class Display
{
public:
	Display();
	~Display();

	void Initialize();
	void PollEvents();
	void Shutdown();
	bool quitRequested = false;

	const int width = 800;
	const int height = 600;
	const int clearColour = 0x00000000;

	void PutPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char p);
	void PutPixel(int x, int y, int colour);
	void FlipFromIntPtr(int* source);

	void ClearPixelbuffer();
	void PresentPixelbufferToWindow();

	int* pixelBuffer = nullptr;
private:
	HWND windowHandle = nullptr;
	static LRESULT CALLBACK MainWindowProcedure(HWND windowHandle, UINT message, WPARAM wparam, LPARAM lparam);

	BITMAPINFO pixelbufferInfo = {};
	WNDCLASS windowClassInfo = {};
};
