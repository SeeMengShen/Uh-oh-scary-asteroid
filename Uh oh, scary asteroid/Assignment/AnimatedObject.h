#ifndef ANIMATED_OBJECT_H
#define ANIMATED_OBJECT_H

#pragma once
#include <iostream>
#include "Texture.h"
#include "SpriteSheet.h"
#include "GameObject.h"
#include <d3dx9.h>
#include "TransformationMatrix.h"
using namespace std;

class AnimatedObject: public GameObject
{
private:
	int animationFPS;
	int currentFrame;
	int characterAnimation;

public:
	AnimatedObject(string name,
		SpriteSheet* spriteSheet,
		TransformationMatrix* transformMatrix,
		int red,
		int green,
		int blue,
		D3DXVECTOR2* position,
		float force,
		float mass,
		int animationFPS);

	SpriteSheet* getSprite();

	void setCharacterAnimation(int animation);
	void setCurrentFrame(int cFrame);

	int getAnimationFPS();
	int getCurrentFrame();
	int getCharacterAnimation();

	void addCurrentFrame();
	void resetCurrentFrame();

	void updateSprite();
};

#endif