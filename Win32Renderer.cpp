#include "Win32Rendering.h"
#include <string>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")

static const wchar_t s_windowClassName[] = L"CRUDSampleWindowClass";

Win32Renderer::~Win32Renderer() {
	shutdown();
}

bool Win32Renderer::init(HINSTANCE hInstance, int nCmdShow) {
	this->hInstance_ = hInstance;
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = Win32Renderer::staticWndProc;
	wc.hInstance = hInstance_;
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszClassName = s_windowClassName;

	if (!RegisterClassEx(&wc)) {
		MessageBox(nullptr, L"Failed to register window class!", L"Error", MB_ICONERROR);
		return false;
	}

	HWND hWnd = CreateWindowEx(0, s_windowClassName, L"CRUD Sample Application", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, nullptr, nullptr, hInstance_, this/*pass pointer for WM_CREATE*/);

	if (!hWnd) {
		MessageBox(nullptr, L"Failed to create window!", L"Error", MB_ICONERROR);
		return false;
	}

	hWnd_ = hWnd;
	ShowWindow(hWnd_, nCmdShow);
	UpdateWindow(hWnd_);
	return true;
}
/*
int Win32Renderer::run() {
	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return static_cast<int>(msg.wParam);
}
*/

void Win32Renderer::shutdown() {
	if (hWnd_) {
		DestroyWindow(hWnd_);
		hWnd_ = nullptr;
	}
	if (hInstance_) {
		UnregisterClass(s_windowClassName, hInstance_);
		hInstance_ = nullptr;
	}
}


LRESULT CALLBACK Win32Renderer::staticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hWnd, message, wParam, lParam);
}

LRESULT Win32Renderer::WNDProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}