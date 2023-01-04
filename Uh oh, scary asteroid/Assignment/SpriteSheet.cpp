#include "SpriteSheet.h"
using namespace std;

SpriteSheet::SpriteSheet(string texturePath,
	int textureWidth,
	int textureHeight,
	int spriteRow,
	int spriteCol,
	int maxFrame) : Texture(texturePath,
		textureHeight,
		textureWidth)
{
	this->spriteRow = spriteRow;
	this->spriteCol = spriteCol;
	this->maxFrame = maxFrame - 1;
}

SpriteSheet::SpriteSheet(string texturePath,
	int textureWidth,
	int textureHeight,
	int alphaRed,
	int alphaGreen,
	int alphaBlue,
	int spriteRow,
	int spriteCol,
	int maxFrame) : Texture(texturePath,
		textureHeight,
		textureWidth,
		alphaRed,
		alphaGreen,
		alphaBlue)
{
	this->spriteRow = spriteRow;
	this->spriteCol = spriteCol;
	this->maxFrame = maxFrame - 1;
}

int SpriteSheet::getSpriteRow() { return spriteRow; }
int SpriteSheet::getSpriteCol() { return spriteCol; }
int SpriteSheet::getMaxFrame() { return maxFrame; }

void SpriteSheet::setMaxFrame(int max) { this->maxFrame = max; }