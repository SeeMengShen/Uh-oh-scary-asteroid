#ifndef SPRITE_SHEET_H
#define SPRITE_SHEET_H

#pragma once
#include <iostream>
#include <d3dx9.h>
#include "Texture.h"
using namespace std;

class SpriteSheet: public Texture
{
private:
	int spriteRow;
	int spriteCol;
	int maxFrame;

public:
	SpriteSheet(string texturePath,
		int textureHeight,
		int textureWidth,
		int spriteRow, 
		int spriteCol,
		int maxFrame);

	SpriteSheet(string texturePath,
		int textureHeight,
		int textureWidth,
		int alphaRed,
		int alphaGreen,
		int alphaBlue,
		int spriteRow,
		int spriteCol,
		int maxFrame);

	int getSpriteRow();
	int getSpriteCol();
	int getMaxFrame();

	void setMaxFrame(int max);
};

#endif