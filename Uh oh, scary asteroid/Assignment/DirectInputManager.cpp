#include "DirectInputManager.h"
#include <iostream>
#include "WindowsManager.h"
using namespace std;

LPDIRECTINPUTDEVICE8 DirectInputManager::dInputKeyboardDevice = NULL;
LPDIRECTINPUTDEVICE8 DirectInputManager::dInputMouseDevice = NULL;
DIMOUSESTATE DirectInputManager::mouseState;
BYTE DirectInputManager::diKeys[256];

void checkHr(HRESULT hr, string forWhat)
{
	if (FAILED(hr))
		cout << "Failed to " + forWhat + "\n";
	else
		cout << forWhat + " success\n";
}

void DirectInputManager::createDInput(HWND g_hWnd)
{
	//	Create the Direct Input object.
	HRESULT hr = DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, (void**)&dInput, NULL);

	checkHr(hr, "create DI object");

	//	Create the keyboard device.
	hr = dInput->CreateDevice(GUID_SysKeyboard, &dInputKeyboardDevice, NULL);
	checkHr(hr, "create virtual keyboard");
	hr = dInput->CreateDevice(GUID_SysMouse, &dInputMouseDevice, NULL);
	checkHr(hr, "create virtual mouse");

	//	Set the input data format.
	hr = dInputKeyboardDevice->SetDataFormat(&c_dfDIKeyboard);
	checkHr(hr, "set keyboard data format");
	hr = dInputMouseDevice->SetDataFormat(&c_dfDIMouse);
	checkHr(hr, "set mouse data format");

	//	Set the cooperative level.
	//	To Do:
	//	Try with different combination.
	hr = dInputKeyboardDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	checkHr(hr, "set keyboard cooperative level");
	hr = dInputMouseDevice->SetCooperativeLevel(g_hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	checkHr(hr, "set mouse cooperative level");
}

void DirectInputManager::cleanupDInput()
{
	//	Release keyboard device.
	dInputKeyboardDevice->Unacquire();
	dInputKeyboardDevice->Release();
	dInputKeyboardDevice = NULL;

	dInputMouseDevice->Unacquire();
	dInputMouseDevice->Release();
	dInputMouseDevice = NULL;

	//	Release DirectInput.
	dInput->Release();
	dInput = NULL;
}
