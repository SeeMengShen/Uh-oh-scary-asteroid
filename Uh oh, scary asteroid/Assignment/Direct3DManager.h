#ifndef DIRECT3DMANAGER_H

#define DIRECT3DMANAGER_H

#pragma once
#include <d3d9.h>
#include <d3dx9core.h>
class Direct3DManager
{
public:
	//	Virtual Graphic Card
	static IDirect3DDevice9* d3dDevice;

	//	Render brush
	static LPD3DXSPRITE spriteBrush;
	static LPD3DXFONT font;
	static LPD3DXFONT titleFont;
	static LPD3DXLINE lineBrush;

	void createD3D(HWND g_hWnd);
	void cleanupD3D();
};

#endif