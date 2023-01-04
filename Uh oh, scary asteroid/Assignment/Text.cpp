#include "Text.h"

Text::Text(string str,
	int red,
	int green,
	int blue)
{
	this->str = str;
	this->red = red;
	this->green = green;
	this->blue = blue;

	this->textRect = new RECT();

	setRect(0, 0, 0, 0);

	titleFont = false;
}

Text::Text(string str,
	int rectLeft,
	int rectTop,
	int rectRight,
	int rectBottom,
	int red,
	int green,
	int blue,
	D3DXVECTOR2* positionRelativeToPanel,
	bool titleFont)
{
	this->str = str;
	this->textRect = new RECT();
	this->rectLeft = rectLeft;
	this->rectTop = rectTop;
	this->rectRight = rectRight;
	this->rectBottom = rectBottom;
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->positionRelativeToPanel = positionRelativeToPanel;
	this->titleFont = titleFont;
}

string Text::getStr() { return str; }
RECT* Text::getTextRect() { return textRect; }
D3DXVECTOR2* Text::getPositionRelativeToPanel() { return positionRelativeToPanel; }
int Text::getRed() { return red; }
int Text::getGreen() { return green; }
int Text::getBlue() { return blue; }

int Text::getRectRight() { return rectRight; }

int Text::getRectBottom() { return rectBottom; }

bool Text::isTitleFont()
{
	return titleFont;
}

void Text::setRect(int rectLeft, int rectRight, int rectTop, int rectBottom)
{
	textRect->left = rectLeft;
	textRect->right = rectRight;
	textRect->top = rectTop;
	textRect->bottom = rectBottom;
}

void Text::setText(string str)
{
	this->str = str;
}

void Text::cleanup()
{
	cout << "\nCleanup text : " + str;
	delete textRect;
	textRect = NULL;

	delete positionRelativeToPanel;
	positionRelativeToPanel = NULL;
	cout << " SUCCESSFUL" << endl;
}