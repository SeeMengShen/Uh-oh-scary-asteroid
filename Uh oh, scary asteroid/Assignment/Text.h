#ifndef TEXT_H
#define TEXT_H

#pragma once
#include <iostream>
#include "AnimatedObject.h"

using namespace std;

class Text
{
public:
	string str;
	RECT* textRect;
	int rectLeft;
	int rectRight;
	int rectTop;
	int rectBottom;
	D3DXVECTOR2* positionRelativeToPanel;
	int red;
	int green;
	int blue;
	bool titleFont;

	Text(string str,
		int red,
		int green,
		int blue);

	Text(string str,
		int rectLeft,
		int rectTop,
		int rectRight,
		int rectBottom,
		int red,
		int green,
		int blue,
		D3DXVECTOR2* positionRelativeToPanel,
		bool titleFont);

	string getStr();
	RECT* getTextRect();
	D3DXVECTOR2* getPositionRelativeToPanel();
	int getRed();
	int getGreen();
	int getBlue();
	int getRectRight();
	int getRectBottom();
	bool isTitleFont();

	void setRect(int rectLeft, int rectRight, int rectTop, int rectBottom);
	void setText(string str);

	void cleanup();
};

#endif