#include "Header1.h"
#include "Win32Rendering.h"
#include <Windows.h>
#include <crtdbg.h>
/*
#ifdef _MSC_VER
#  if __has_include(<vld.h>)
#    include <vld.h>
#  endif
#endif
*/
#include <iostream>

int main() {
	MessageBox(nullptr, L"Welcome to the CRUD Sample Application!", L"CRUD Sample", MB_OK | MB_ICONINFORMATION);
	//Win32Renderer wr;
	CRUD::Application app;
	app.run();
	//wr.run();
	std::cout << "CRUD\n";
	_CrtDumpMemoryLeaks();
	return 0;
}