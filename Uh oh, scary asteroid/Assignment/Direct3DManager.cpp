#include "Direct3DManager.h"
#include "WindowsManager.h"
#include <iostream>
using namespace std;

IDirect3DDevice9* Direct3DManager::d3dDevice = NULL;
LPD3DXSPRITE Direct3DManager::spriteBrush = NULL;
LPD3DXFONT Direct3DManager::font = NULL;
LPD3DXFONT Direct3DManager::titleFont = NULL;
LPD3DXLINE Direct3DManager::lineBrush = NULL;

void Direct3DManager::createD3D(HWND g_hWnd)
{
	//	Define Direct3D 9. [Object]
	IDirect3D9* direct3D9 = Direct3DCreate9(D3D_SDK_VERSION);

	//	Define how the screen presents.
	D3DPRESENT_PARAMETERS d3dPP;
	ZeroMemory(&d3dPP, sizeof(d3dPP));

	//	Refer to Direct3D 9 documentation for the meaning of the members.
	d3dPP.Windowed = true;
	d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dPP.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dPP.BackBufferCount = 1;
	d3dPP.BackBufferWidth = WindowsManager::windowsWidth;
	d3dPP.BackBufferHeight = WindowsManager::windowsHeight;
	d3dPP.hDeviceWindow = g_hWnd;

	//	Create a Direct3D 9 device. [Virtual Graphic Card]
	HRESULT hr = direct3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL /*D3DDEVTYPE_REF*/, g_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dPP, &d3dDevice);

	if (FAILED(hr))
		cout << "Failed to create virtual graphic card" << endl;
	else
		cout << "create virtual graphic card success" << endl;

	hr = D3DXCreateSprite(d3dDevice, &spriteBrush);

	if (FAILED(hr))
		cout << "Failed to create sprite brush" << endl;
	else
		cout << "create sprite brush success" << endl;

	hr = D3DXCreateLine(d3dDevice, &lineBrush);

	if (FAILED(hr))
		cout << "Failed to create line brush" << endl;
	else
		cout << "create line brush success" << endl;

	font = NULL;
	hr = D3DXCreateFont(d3dDevice, 32, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Rockwell", &font);

	if (FAILED(hr))
		cout << "Failed to create font brush" << endl;
	else
		cout << "create font brush success" << endl;

	titleFont = NULL;
	hr = D3DXCreateFont(d3dDevice, 45, 0, 0, 1, false,
		DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "Rockwell", &titleFont);

	if (FAILED(hr))
		cout << "Failed to create title font brush" << endl;
	else
		cout << "create title font brush success" << endl;
}

void Direct3DManager::cleanupD3D()
{
	//	Release the device when exiting.
	d3dDevice->Release();
	//	Reset pointer to NULL, a good practice.
	d3dDevice = NULL;

	spriteBrush->Release();
	spriteBrush = NULL;

	font->Release();
	font = NULL;

	titleFont->Release();
	titleFont = NULL;

	lineBrush->Release();
	lineBrush = NULL;
}