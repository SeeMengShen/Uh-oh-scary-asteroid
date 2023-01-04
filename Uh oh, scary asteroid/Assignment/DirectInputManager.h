#ifndef DIRECTINPUTMANAGER_H

#define DIRECTINPUTMANAGER_H

#pragma once
#include <dinput.h>
class DirectInputManager
{

public:
	//	Direct Input object.
	LPDIRECTINPUT8 dInput;

	//	Direct Input keyboard device.
	static LPDIRECTINPUTDEVICE8 dInputKeyboardDevice;
	static LPDIRECTINPUTDEVICE8 dInputMouseDevice;

	static DIMOUSESTATE mouseState;

	//	Key input buffer
	static BYTE diKeys[256];

	void createDInput(HWND g_hWnd);
	void cleanupDInput();
};

#endif