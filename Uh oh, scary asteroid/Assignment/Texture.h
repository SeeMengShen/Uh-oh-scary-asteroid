#ifndef TEXTURE_H
#define TEXTURE_H

#pragma once
#include <iostream>
#include <d3dx9.h>
using namespace std;

class Texture
{
protected:
	string texturePath;
	int textureHeight;
	int textureWidth;
	LPDIRECT3DTEXTURE9 directTexture;
	int alphaRed;
	int alphaGreen;
	int alphaBlue;

public:
	Texture(string texturePath, 
		int textureHeight, 
		int textureWidth);

	Texture(string texturePath,
		int textureHeight,
		int textureWidth,
		int alphaRed,
		int alphaGreen,
		int alphaBlue);

	string getTexturePath();
	int getTextureHeight();
	int getTextureWidth();
	int getAlphaRed();
	int getAlphaGreen();
	int getAlphaBlue();
	LPDIRECT3DTEXTURE9 getTexturePointer();

	void nullTexturePointer();
};

#endif