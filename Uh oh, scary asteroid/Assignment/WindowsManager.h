#ifndef WINDOWSMANAGER_H

#define WINDOWSMANAGER_H

#pragma once
#include <Windows.h>

class WindowsManager
{

public:
	//	Window's structure
	WNDCLASS wndClass;

	//	Window handle
	HWND g_hWnd = NULL;

	static const int windowsWidth = 800;
	static const int windowsHeight = 600;

	void createWindow();
	static LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	bool windowIsRunning();
	void cleanupWindow();
};

#endif