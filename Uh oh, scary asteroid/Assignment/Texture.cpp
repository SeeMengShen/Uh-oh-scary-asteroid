#include "Texture.h"
#include "Direct3DManager.h"
using namespace std;

Texture::Texture(string texturePath,
	int textureHeight,
	int textureWidth) 
{
	this->texturePath = texturePath;
	this->textureHeight = textureHeight;
	this->textureWidth = textureWidth;

	HRESULT hr = D3DXCreateTextureFromFile(Direct3DManager::d3dDevice, this->texturePath.c_str(), &directTexture);

	if (FAILED(hr))
		cout << "Failed to create texture " + this->texturePath + "\n";
	else
		cout << "Create texture " + this->texturePath + " success\n";
}

Texture::Texture(string texturePath,
	int textureHeight,
	int textureWidth,
	int alphaRed,
	int alphaGreen,
	int alphaBlue)
{
	this->texturePath = texturePath;
	this->textureHeight = textureHeight;
	this->textureWidth = textureWidth;
	this->alphaRed = alphaRed;
	this->alphaGreen = alphaGreen;
	this->alphaBlue = alphaBlue;

	HRESULT hr = D3DXCreateTextureFromFile(Direct3DManager::d3dDevice, this->texturePath.c_str(), &directTexture);

	if (FAILED(hr))
		cout << "Failed to create texture " + this->texturePath + "\n";
	else
		cout << "Create texture " + this->texturePath + " success\n";
}

string Texture::getTexturePath() { return texturePath; }
int Texture::getTextureHeight() { return textureHeight; }
int Texture::getTextureWidth() { return textureWidth; }
LPDIRECT3DTEXTURE9 Texture::getTexturePointer() { return directTexture; }
int Texture::getAlphaRed() { return alphaRed; }
int Texture::getAlphaGreen() { return alphaGreen; }
int Texture::getAlphaBlue() { return alphaBlue; }

void Texture::nullTexturePointer() { directTexture = NULL; }