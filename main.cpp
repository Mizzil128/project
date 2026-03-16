#include "Header1.h"
#include "Win32Rendering.h"
#include <Windows.h>
#include <iostream>

int main() {
	MessageBox(nullptr, L"Welcome to the CRUD Sample Application!", L"CRUD Sample", MB_OK | MB_ICONINFORMATION);
	//Win32Renderer wr;
	CRUD::Application app;
	app.run();
	//wr.run();
	std::cout << "CRUD\n";
	return 0;
}