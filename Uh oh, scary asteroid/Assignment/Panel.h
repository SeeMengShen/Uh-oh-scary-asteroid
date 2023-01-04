#ifndef PANEL_H
#define PANEL_H
#pragma once

#include "Text.h"
#include "Button.h"

#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>
#include <vector>

class Panel
{
public:
	Panel(D3DXVECTOR2* positionRelativeToWindow);

	D3DXVECTOR2* getPositionRelativeToWindow();
	vector<Button*> vecBtns;
	vector<Text*> vecLbls;
	
	void cleanup();

private:
	D3DXVECTOR2* positionRelativeToWindow;
};

#endif