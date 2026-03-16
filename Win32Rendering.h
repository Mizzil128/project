#pragma once
#include <Windows.h>

class Win32Renderer {
	public:
		Win32Renderer() = default;
		~Win32Renderer();

		bool init(HINSTANCE hInstance, int nCmdShow=SW_SHOWDEFAULT);
		int run();
		void shutdown();
	private:
		HINSTANCE hInstance_{nullptr};
		HWND hWnd_{nullptr};

		static LRESULT CALLBACK staticWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		LRESULT WNDProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};