#include "Panel.h"
#include <vector>
using namespace std;

Panel::Panel(D3DXVECTOR2* positionRelativeToWindow)
{
	this->positionRelativeToWindow = positionRelativeToWindow;
}

D3DXVECTOR2* Panel::getPositionRelativeToWindow() { return positionRelativeToWindow; }

void Panel::cleanup()
{
	for (auto btn : vecBtns)
	{
		btn->cleanup();
		delete btn;
		btn = NULL;
	}

	for (auto lbl : vecLbls)
	{
		lbl->cleanup();
		delete lbl;
		lbl = NULL;
	}

	delete positionRelativeToWindow;
	positionRelativeToWindow = NULL;
}