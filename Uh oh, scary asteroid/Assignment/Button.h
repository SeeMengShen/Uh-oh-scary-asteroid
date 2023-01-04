#ifndef BUTTON_H
#define BUTTON_H
#pragma once

#include "Text.h"
#include "Texture.h"

#include <iostream>
#include <d3d9.h>
#include <d3dx9.h>
using namespace std;

class Button
{
private:
	Texture* texture;
	TransformationMatrix* tm;
	Text* label;
	D3DXVECTOR2* positionRelativeToPanel;
	RECT* buttonRect;
	RECT buttonBoxCollider;
	bool mouseOn;

public:
	Button(
		Texture* texture,
		TransformationMatrix* tm,
		Text* label,
		D3DXVECTOR2* positionRelativeToPanel
	);

	Texture* getTexture();
	TransformationMatrix* getTransformationMatrix();
	Text* getLabel();
	D3DXVECTOR2* getPositionRelativeToPanel();
	RECT* getButtonRect();
	RECT getButtonBoxCollider();
	bool isMouseOn();

	void setMouseOn(bool mouseOn);

	void setButtonBoxCollider(float panelPositionRelativeToWindowsX, float panelPositionRelativeToWindowsY);

	void cleanup();
};

#endif